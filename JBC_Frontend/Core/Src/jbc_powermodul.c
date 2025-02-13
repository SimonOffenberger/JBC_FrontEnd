#include "main.h"
#include "jbc_powermodul.h"
#include "modbus_master.h"

uint32_t P[8]={0};

void collect_data(void){
  ModbusReadAllRegister();
  modbus_handle_res(ModbusReadAllRegister,ModbusRequestReadAllRegister,&P);
}

void set_new_OUT_Temp(int Temperature){

}