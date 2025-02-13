#ifndef __MODBUS_MASTER_H
#define __MODBUS_MASTER_H

#include "stm32f7xx_hal.h"

typedef void (*funcptr)(void);

#define MAXFRAMESIZE 32
#define RESENDTIMEOUT 100
#define RESENDTRYS	5

//Slave Adress
#define ModbusSlaveAdress 0x01
	 
// General Frame Index
#define ModbusIndexSlaveAdr 	0
#define ModbusIndexFunction 	1
#define ModbusIndexByteCount	2

// Simple Read Frame Index
#define ModbusIndexSimpleReadDataHigh 	3
#define ModbusIndexSimpleReadDataLow 		4

// Simple Write Frame Index
#define ModbusIndexSimpleWriteRegisterHigh		2
#define ModbusIndexSimpleWriteRegisterLow 		3
#define ModbusIndexSimpleWriteDataHigh 				4
#define ModbusIndexSimpleWriteDataLow 				5

// Multiple Read Frame Index
#define ModbusIndexMultipleReadByteCount 				2
#define ModbusIndexMultipleReadFirstDataHigh 		3
#define ModbusIndexMultipleReadFirstDataLow 		4

// Multiple Write Rec Frame Index
#define ModbusIndexMultipleWriteAdressHigh 			2
#define ModbusIndexMultipleWriteAdressLow 			3
#define ModbusIndexMultipleWriteNumRegHigh			4
#define ModbusIndexMultipleWriteNumRegLow 			5

// Modbus Functions
#define ModbusFuncSingleRead   		0x04
#define ModbusFuncMultipleRead 		0x03
#define ModbusFuncSingleWrite 		0x06
#define ModbusFuncMultipleWrite 	0x10

// Response Frame Index
#define ModbusFrameIndexByteCount 2

#define ModbusRequestReadAllRegister   1

void ModbusReadAllRegister(void);
uint8_t modbus_handle_res(funcptr resendfunc,uint8_t request,uint32_t * data);

#endif
