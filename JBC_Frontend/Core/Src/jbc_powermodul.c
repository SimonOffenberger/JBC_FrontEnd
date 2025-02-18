#include "main.h"
#include "jbc_powermodul.h"
#include "modbus_master.h"

uint32_t P[8]={0};

void ModbusReadAllRegister(void){
	Modbus_multipleRead(0,8);
}

void ModbusSetNewOutTemp1(){
	Modbus_singleWrite(PARAM_SET_TEMPERATURE_OUT1,P[PARAM_SET_TEMPERATURE_OUT1]);
}

void collect_data(void){
  ModbusReadAllRegister();
  modbus_handle_res(ModbusReadAllRegister,ModbusRequestReadAllRegister,P);
}

void set_new_OUT_Temp(int Temperature){
  P[PARAM_ACTUAL_TEMPERATURE_OUT1] = Temperature;
  ModbusSetNewOutTemp1();
  modbus_handle_res(ModbusSetNewOutTemp1,ModbusRequestSetNewTemp,P);

}