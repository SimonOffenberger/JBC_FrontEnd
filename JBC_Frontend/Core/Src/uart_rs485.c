#include "main.h"
#include "uart_rs485.h"
#include "string.h"

volatile UART_rs485_protocol_var 	uart_rs485_flags;			// deklaration der uart debug Flags
 DMA_HandleTypeDef 	hdma_usart_rs485_tx;

 /*********************************** UART Callbacks *************************************************************/
/// @brief RX Callback der UART
/// @param  void
void UART_RS485_rx_callback(void){
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
	uart_rs485_flags.rx_buffer[uart_rs485_flags.rx_wPos] = uart_rs485_flags.rcv_byte;
		if (++uart_rs485_flags.rx_wPos >= UART_RX_RS485_BUFFER_SIZE) {
				uart_rs485_flags.rx_wPos = 0;
		}
		if (uart_rs485_flags.rx_wPos == uart_rs485_flags.rx_rPos) {			// bei PufferÃ¼berlauf letztes Zeichen ueberschreiben
				if (++uart_rs485_flags.rx_rPos >= UART_RX_RS485_BUFFER_SIZE) {
						uart_rs485_flags.rx_rPos = 0;
				}
		}
	HAL_UART_Receive_IT(&huart6,(uint8_t *) &uart_rs485_flags.rcv_byte,1);
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET);

}

/// @brief TX Callback der Uart 
/// @param  void
void UART_RS485_tx_callback(void){
	uart_rs485_flags.tx_active = 0;
	uart_rs485_flags.tx_wPos=0;
}

/// @brief Error Callback der Uart 
/// @param  void
void UART_RS485_error_callback(void){

}

/// @brief Funktion zum Löschen des Empfangsbuffers der Step Driver UART
/// @param  void
void UART_RS485_clear_buffer(void){
	uart_rs485_flags.rx_wPos=0;
	uart_rs485_flags.rx_rPos=0;
}

/*********************************** UART Transmit-Functions *************************************************************/
/// @brief Funktion zum Übertragen eines Chars über die  Uart
/// @param c Char der Übertragen werden soll
void UART_RS485_transmit_char(char c){
		uint8_t ch[1];
		ch[0] = c;
	
		while(uart_rs485_flags.tx_active){
			uart_rs485_flags.time_out++;
			HAL_Delay(1);
			if(uart_rs485_flags.time_out >= UART_RS485_TIMEOUT){
				uart_rs485_flags.tx_active = 0;
				break;
			}
		}
		
		if(uart_rs485_flags.time_out < UART_RS485_TIMEOUT){
			uart_rs485_flags.tx_active = 1;
			uart_rs485_flags.tx_active = 1;
			HAL_UART_Transmit_DMA(&huart6,(uint8_t *)  ch,1);
		}
		uart_rs485_flags.time_out = 0;	                     
}


/// @brief Diese Funktion sendet einen CRLF über die Uart raus
/// @param  void
void UART_RS485_transmit_crlf (void){
	UART_RS485_transmit_char(0x0D);
	UART_RS485_transmit_char(0x0A);

}
/// @brief Überträgt einen String über die Uart
/// @param s String der Übertragen werden soll
void UART_RS485_transmit_string(char *s){


	while(uart_rs485_flags.tx_active){
		uart_rs485_flags.time_out++;
			HAL_Delay(1);
		if(uart_rs485_flags.time_out >= UART_RS485_TIMEOUT){
			uart_rs485_flags.tx_active = 0;
			break;
		}
	}
	if(uart_rs485_flags.time_out < UART_RS485_TIMEOUT){
		uart_rs485_flags.tx_active = 1;
		HAL_UART_Transmit_DMA(&huart6,(uint8_t *) s,strlen((char*)s));
	}
	uart_rs485_flags.time_out = 0;		
}
/// @brief Überträgt ein Daten Array über die Uart
/// @param data Daten Array Pointer
/// @param len Länge des Arrays
void UART_RS485_transmit_data(uint8_t *s, uint16_t len){

		while(uart_rs485_flags.tx_active){
			uart_rs485_flags.time_out++;
			HAL_Delay(1);
			if(uart_rs485_flags.time_out >= UART_RS485_TIMEOUT){
				uart_rs485_flags.tx_active = 0;
				break;
			}
		}
		if(uart_rs485_flags.time_out < UART_RS485_TIMEOUT){

			uart_rs485_flags.tx_active = 1;
			uart_rs485_flags.tx_wPos = 0;
		for(uint8_t i=0;i<len;i++){
			uart_rs485_flags.tx_buffer[i+uart_rs485_flags.tx_wPos] = s[i];
		}
		uart_rs485_flags.tx_wPos += len;
		HAL_UART_Transmit_DMA(&huart6,(uint8_t *)uart_rs485_flags.tx_buffer,len);
	}
	
	uart_rs485_flags.time_out = 0;		
	
}

/// @brief Funktion zum umdrehen eines Strings
/// @param s 
void reverse(uint8_t *s){
	uint32_t c, i, j;

	for (i = 0, j = strlen((char*)s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/// @brief Funktion zum Convertieren von UI32 zu String
/// @param n Number die Convertiert werden soll
/// @param s pointer auf den Ausgabe-string
void ui32toa(uint32_t n, uint8_t *s){
	uint16_t i = 0;

	do {       																// generate digits in reverse order
		s[i++] = n % 10 + '0';   								// get next digit
	} while ((n /= 10) > 0);     							// delete it
	s[i] = '\0';
	reverse(s);
}


/// @brief  Funktion zum Übertragen eines ui32 über die Uart 
/// @param i ui32 welches übertragen werden soll
void UART_RS485_transmit_ui32(uint32_t i){

		uint8_t s[12];
		uint8_t len = 0;
		
		ui32toa(i,s);

		while(s[len]!='\0'){	
			UART_RS485_transmit_char(s[len]);
			len++;
		}	
}



/*********************************** UART Receive-Functions *************************************************************/
/// @brief Funktion zum Auslesn der Länger der Daten im Empfangsbuffer
/// @param  void
/// @return Länge der ungelesenen Daten im Empfangsbuffer 
uint16_t UART_RS485_get_len(void){
	uint16_t	result = 0;
	
	if ((result = uart_rs485_flags.rx_wPos  - uart_rs485_flags.rx_rPos ) >= UART_RX_RS485_BUFFER_SIZE) {
		result += UART_RX_RS485_BUFFER_SIZE;
	}
	return (result);
}

/// @brief Liest Daten aus dem Emfangsbuffer aus wenn welche drinnen stehen
/// @param  void
/// @return char der aus den Empfangsbuffer stammt
char UART_RS485_get_c_nowait(void){
	char result = 0;

  if (UART_RS485_get_len()) {
		result = uart_rs485_flags.rx_buffer[uart_rs485_flags.rx_rPos];
		if (++uart_rs485_flags.rx_rPos  >= UART_RX_RS485_BUFFER_SIZE){
				uart_rs485_flags.rx_rPos = 0;
		}
	}
	return (result);
}

/// @brief Liest Daten aus dem Emfangsbuffer aus wenn welche drinnen stehen
/// @param  void
/// @return char der aus den Empfangsbuffer stammt
/// @note Wenn keine Daten drinnen stehen wird gewartet -> kein Timeout in dieser Funktion !!!!!!
char UART_RS485_get_c_wait(void){
	char c;

	while ((c = UART_RS485_get_c_nowait()) == 0x00) {
	}
	return (c);
}

/// @brief Liest eine Zahl aus dem Empfangsbuffer aus als Trennzeichen gilt '-'
/// @param  void
/// @return Zahl aus dem Emfpangsbuffer
uint32_t UART_RS485_get_number(void){
		uint32_t result = 0;
		uint8_t tmp[11]={0,0,0,0,0,0,0,0,0,0};
		uint8_t i = 0;


    	while( (tmp[i] = UART_RS485_get_c_wait()) != '-'){

            tmp[i]=(tmp[i]-48);	// von ASCII auf bin
            i++;
        }

        tmp[i] = 0;
        i-=1;


        if(i==0)	    result = tmp[0]*1UL;
        else if(i==1)	result = tmp[0]*10 + tmp[1]*1UL;
        else if(i==2)	result = tmp[0]*100 + tmp[1]*10 + tmp[2]*1UL;
        else if(i==3)	result = tmp[0]*1000 + tmp[1]*100 + tmp[2]*10 + tmp[3]*1UL;
        else if(i==4)	result = tmp[0]*10000 + tmp[1]*1000 + tmp[2]*100 + tmp[3]*10 + tmp[4]*1UL;
        else if(i==5)	result = tmp[0]*100000 + tmp[1]*10000 + tmp[2]*1000 + tmp[3]*100 + tmp[4]*10 + tmp[5]*1UL;
        else if(i==6)	result = tmp[0]*1000000 + tmp[1]*100000 + tmp[2]*10000 + tmp[3]*1000 + tmp[4]*100 + tmp[5]*10 + tmp[6]*1UL;
        else if(i==7)	result = tmp[0]*10000000 + tmp[1]*1000000 + tmp[2]*100000 + tmp[3]*10000 + tmp[4]*1000 + tmp[5]*100 + tmp[6]*10 + tmp[7]*1UL;
        else if(i==8)	result = tmp[0]*100000000 + tmp[1]*10000000 + tmp[2]*1000000 + tmp[3]*100000 + tmp[4]*10000 + tmp[5]*1000 + tmp[6]*100 + tmp[7]*10 + tmp[8]*1UL;
        else if(i==9)	result = tmp[0]*1000000000 + tmp[1]*100000000 + tmp[2]*10000000 + tmp[3]*1000000 + tmp[4]*100000 + tmp[5]*10000 + tmp[6]*1000 + tmp[7]*100 + tmp[8]*10 + tmp[9]*1UL;
        else        result = 0xFFFFFFFF;

		return result;

}
	

/// @brief Callback für UART Receive
/// @param uart Pointer auf die Uart Handle Struct
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *uart){
    if(uart == &huart6){
				UART_RS485_rx_callback();
    }
}

/// @brief Callback für UART Transmit
/// @param uart Pointer auf die UART Handle Struct
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *uart){
  if(uart == &huart6){
				UART_RS485_tx_callback();
    }
}


/// @brief Error Callback, der UART
/// @param uart Pointer auf die UART Handle Struct
void HAL_UART_ErrorCallback(UART_HandleTypeDef *uart){
	if(uart == &huart6){
				UART_RS485_error_callback();
    }

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
