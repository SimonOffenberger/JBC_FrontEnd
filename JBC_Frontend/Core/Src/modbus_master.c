#include "main.h"
#include "modbus_master.h"
#include "uart_rs485.h"
uint8_t recFrame[MAXFRAMESIZE]={0};



// Function Prototyps
uint8_t modbus_handle_res(funcptr resendfunc,uint8_t request,uint32_t* data);
void show_mischer_debug_info(void);
void modbus_initialize_Pause_Time(void);
void Modbus_read_HW_SW_VERSION(void);

uint16_t calc_CRC_master(uint8_t* frame, uint16_t len)
{
	uint16_t crc = 0xFFFF;

	for (int pos = 0; pos < len; pos++)
	{
			crc ^= (uint16_t)frame[pos];          // XOR byte into least sig. byte of crc

			for (int i = 8; i != 0; i--)
			{    // Loop over each bit
					if ((crc & 0x0001) != 0)
					{      														// If the LSB is set
							crc >>= 1;                    // Shift right and XOR 0xA001
							crc ^= 0xA001;
					}
					else                            	// Else LSB is not set
							crc >>= 1;                    // Just shift right
			}
	}
	// Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
	//Now the crc is in little endian, but we need it in big endian;

	uint8_t lowercrc = 0;
	uint8_t highercrc = 0;

	highercrc = (uint8_t)((crc >> 8) & 0xFF);           // extract higher byte
	lowercrc = (uint8_t)((crc) & 0x00FF);             // extract lower byte

	crc = (uint16_t)(((uint16_t)lowercrc << (uint8_t)8) + (uint8_t)highercrc);        // swap the two bytes

	return crc;
}

void Modbus_singleRead(uint16_t reg)
{
		static uint8_t frame[8];
		uint16_t checksum = 0;
	
		frame[0] = ModbusSlaveAdress;            // slave addresse
		frame[1] = ModbusFuncSingleRead;         // Function for single Read
		frame[2] = (uint8_t)((reg >> 8) & 0xFF);  // Register addresse high
		frame[3] = (uint8_t)((reg) & 0x00FF);     // Register addresse low
		frame[4] = 0x00;                          // Number of registers high
		frame[5] = 0x01;                          // Number of registers low

		checksum = calc_CRC_master(frame,6);

		frame[6] = (uint8_t)((checksum >> 8) & 0xFF);       // crc high
		frame[7] = (uint8_t)((checksum) & 0x00FF);          // crc low
		
		UART_RS485_transmit_data(frame,sizeof(frame));  // send frame
	
}

void Modbus_singleWrite(uint16_t reg,uint16_t data)
{
		static uint8_t frame[8];
		uint16_t checksum = 0;


		frame[0] = ModbusSlaveAdress;                 // slave addresse
		frame[1] = ModbusFuncSingleWrite;             // Function for single Read
		frame[2] = (uint8_t)((reg >> 8) & 0xFF);  		 // Register addresse high
		frame[3] = (uint8_t)((reg) & 0x00FF);     		 // Register addresse low
		frame[4] = (uint8_t)((data >> 8) & 0xFF);      // Register addresse high
		frame[5] = (uint8_t)((data) & 0x00FF);         // Register addresse low

		checksum = calc_CRC_master(frame,6);

		frame[6] = (uint8_t)((checksum >> 8) & 0xFF);       // crc high
		frame[7] = (uint8_t)((checksum) & 0x00FF);          // crc low

		UART_RS485_transmit_data(frame,sizeof(frame));  // send frame
}

void Modbus_multipleRead(uint16_t reg, uint16_t numReg)
{
		static uint8_t frame[8];
		uint16_t checksum = 0;

		frame[0] = 0x01;                            	 // slave addresse
		frame[1] = ModbusFuncMultipleRead;            // Function for single Read
		frame[2] = (uint8_t)((reg >> 8) & 0xFF);  		 // Register addresse high
		frame[3] = (uint8_t)((reg) & 0x00FF);     		 // Register addresse low
		frame[4] = (uint8_t)((numReg >> 8) & 0xFF);    // Register addresse high
		frame[5] = (uint8_t)((numReg) & 0x00FF);       // Register addresse low

		checksum = calc_CRC_master(frame, 6);

		frame[6] = (uint8_t)((checksum >> 8) & 0xFF);       // crc high
		frame[7] = (uint8_t)((checksum) & 0x00FF);          // crc low

	UART_RS485_transmit_data(frame,sizeof(frame));  // send frame
}

void Modbus_multipleWrite(uint16_t reg, uint16_t numReg, uint16_t* data)
{
		uint8_t frame_length = 9+2*numReg;
		static uint8_t frame[MAXFRAMESIZE];
		uint16_t checksum = 0;

		frame[0] = 0x01;                            	 // slave addresse
		frame[1] = ModbusFuncMultipleWrite;     	     // Function for single Read
		frame[2] = (uint8_t)((reg >> 8) & 0xFF);  		 // Register addresse high
		frame[3] = (uint8_t)((reg) & 0x00FF);     		 // Register addresse low
		frame[4] = (uint8_t)((numReg >> 8) & 0xFF);    // Register addresse high
		frame[5] = (uint8_t)((numReg) & 0x00FF);       // Register addresse low
		frame[6] = (uint8_t)(numReg*2);
	
		for (uint16_t i=0;i<numReg;i++)
		{
				frame[7+(i*2)]     = (uint8_t)((data[i] >> 8) & 0xFF);    // Register addresse high
				frame[7+(i*2)+1]   = (uint8_t)((data[i]) & 0x00FF);       // Register addresse low
		}

		checksum = calc_CRC_master(frame, frame_length-2);

		frame[frame_length-2] = (uint8_t)((checksum >> 8) & 0xFF);       // crc high
		frame[frame_length-1] = (uint8_t)((checksum) & 0x00FF);          // crc low

		UART_RS485_transmit_data(frame,frame_length);  // send frame
}


// Length of the differnet frames can be extracted from the document from sedal
uint8_t getExpectedLength(uint8_t function,uint8_t count)
{
	switch (function)
	{
		case ModbusFuncSingleRead:    return 7;
		case ModbusFuncSingleWrite:   return 8;
		case ModbusFuncMultipleRead:  return ((uint8_t)(5 + count));
		case ModbusFuncMultipleWrite: return 8;
		default:   return 0;
	}
}

uint8_t check_received_Function(uint8_t function){
	switch(function){
		case	ModbusFuncSingleRead:   		return 0;
		case	ModbusFuncSingleWrite:  		return 0;
		case	ModbusFuncMultipleRead: 		return 0;
		case	ModbusFuncMultipleWrite:		return 0;
		default:												  return 1;
	}
}

uint8_t check_received_adress(uint8_t slave_adress){
		switch(slave_adress){
		case	ModbusSlaveAdress:   			return 0;
		default:												  return 1;
	}
}

/**
  * @brief This function reads the current msg from the rcv buffer and checks the frame structure.
  * @param none. 
  * @retval 1: OK
  * @retval 0: UNKNOWN FRAME
*/
static uint8_t get_msg(void){
	char c = ' ';
	static uint16_t framePos=0;
	static uint8_t 	recFunction=0;
	static uint8_t expectedLength=0;
	
	while(UART_RS485_get_len()){
		c= UART_RS485_get_c_nowait();
		
		switch(framePos){
			//Start of the frame
			case 0:
				recFrame[framePos]=c;
				framePos++;
				if(check_received_adress(c)){
					expectedLength=0;
					recFunction=0;
					framePos=0;
				}
				break;
			case 1:
				//Function is received
				recFunction = c;
				recFrame[framePos]=c;
				framePos++;
				// check if function is valid
				if(check_received_Function(recFunction)){
					if(check_received_adress(recFunction)){
						expectedLength=0;
						recFunction=0;
						framePos=0;
					}
					else{
						expectedLength=0;
						recFunction=0;
						framePos=0;
						recFrame[framePos]=c;
						framePos++;
					}
				}
				
				break;
			case 2:
				expectedLength = getExpectedLength(recFunction, c);
				recFrame[framePos]=c;
				framePos++;
				break;
			default:
				recFrame[framePos]=c;
				framePos++;
				if (expectedLength == framePos)
				{
						uint16_t recCRC = (uint16_t)	((recFrame[framePos-2] << 8) + recFrame[framePos-1]);
						uint16_t calcedCRC = calc_CRC_master	(recFrame, framePos-2);
					
					if (recCRC == calcedCRC)
					{				
							expectedLength=0;
							recFunction=0;
							framePos=0;
							return 1;
					}
					else
					{
							expectedLength=0;
							recFunction=0;
							framePos=0;
							return 0;
					}
				}
			break;
		}
		return 0;
	}
	return 0;
}

/**
  * @brief This function parses the response and stores the information in the mixer struct.
  * @param request: Parameter that indicates what the request was. 
					 It is used to determine the storeage location of the data
  * @retval 1: UNKNOWN REQUEST
  * @retval 0: OK
*/
uint8_t parseMessageTCU(uint8_t request,uint32_t * reg){

	uint16_t data[MAXFRAMESIZE/2];
	
	uint16_t data_end_pos = recFrame[ModbusFrameIndexByteCount]+ModbusFrameIndexByteCount;
	
	// reassemble the nibbles from their byte form and stroe them in Data
	for(uint16_t i=3;i<=data_end_pos;i+=2){
		data[(i-3)/2]= (recFrame[i] << 8) + recFrame[i+1];
	}
	
	switch(request){
		case ModbusRequestReadAllRegister:
			reg[0]= data[0];
			reg[1]= data[1];
		  reg[2]= data[2];
		  reg[3]= data[3];
			reg[4]= data[4];
			reg[5]= data[5];
		  reg[6]= data[6];
		  reg[7]= data[7];
			return 0;
	}
	return 1;
}



/**
  * @brief This function handles the responce of a modbus request.
  * @param resendfunc: Function pointer to the resend Function. 
					 This function is called on each timeout.
  * @param request: Parameter that indicates what the request was. 
					 It is used in the parse_message function
  * @retval 1: TIMEOUT
  * @retval 0: OK
*/
uint8_t modbus_handle_res(funcptr resendfunc,uint8_t request,uint32_t * data){
	uint16_t resend_timeout=0;
	uint8_t trys=1;
	uint8_t received_msg=0;
	
	// wait till TX has finished
	while(uart_rs485_flags.tx_active&&resend_timeout<= RESENDTIMEOUT){
		HAL_Delay(1);
		resend_timeout++;
	}

	
	// wait for the response
	while((trys < RESENDTRYS) &&(!received_msg)){
		if(get_msg()){
			resend_timeout=0;
			received_msg=1;
			parseMessageTCU(request,data);
		}
		// resend if timeout is reached
		if(resend_timeout>= RESENDTIMEOUT){
			resendfunc();
			resend_timeout=0;
			trys++;
			// wait till TX has finished
			while(uart_rs485_flags.tx_active&&resend_timeout<= RESENDTIMEOUT){
				HAL_Delay(1);
				resend_timeout++;
			}
		}
		
		HAL_Delay(1);
		resend_timeout++;
	}

	
	// return 1 if max trys reached -> timeout
	if((trys >= RESENDTRYS)&&(!received_msg)){
		return 1;
	}
	// return 0 -> OK
	return 0;
}


void ModbusReadAllRegister(void){
	Modbus_multipleRead(0,8);
}

void ModbusSetNewOutTemp1(){
	
}