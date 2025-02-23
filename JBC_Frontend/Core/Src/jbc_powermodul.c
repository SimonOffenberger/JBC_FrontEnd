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
	// HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
  
  static uint32_t m_set_temp=0;
  static uint8_t init=0;
  if(m_set_temp != P[PARAM_SET_TEMPERATURE_OUT1]|| !init){
    set_new_OUT_Temp(P[PARAM_SET_TEMPERATURE_OUT1]);
    m_set_temp = P[PARAM_SET_TEMPERATURE_OUT1];
    init=1;
  }
  
  ModbusReadAllRegister();
  modbus_handle_res(ModbusReadAllRegister,ModbusRequestReadAllRegister,P);
	// HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_RESET);

}

void set_new_OUT_Temp(int Temperature){
  P[PARAM_SET_TEMPERATURE_OUT1] = Temperature;
  ModbusSetNewOutTemp1();
  modbus_handle_res(ModbusSetNewOutTemp1,ModbusRequestSetNewTemp,P);
}