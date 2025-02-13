#ifndef JBC_POWERMODUL_H
#define JBC_POWERMODUL_H

#include "stm32f7xx_hal.h"

	// Parameterliste (32-Bit-Werte, Mehrfachbel�gung m�glich)
	enum {
		PARAM_HW_SW_VERSION = 0,							// 0 - Soft- und Hardwareversion 
		PARAM_VDIP1,													// 1 - Virtueller DIP 1 zum aktivieren/deaktivieren von Funktionen
		PARAM_BENUTZERSTATUS,									// 2 - Zust�nde Der Software, Armaturen- bzw. Benutzerstatus (Bus,Andwendung,Reed TD,�)		
		PARAM_SET_TEMPERATURE_OUT1,
		PARAM_ACTUAL_TEMPERATURE_OUT1,
		PARAM_HEATER_POWER_OUT1,
		PARAM_SET_TEMPERATURE_OUT2,
		PARAM_ACTUAL_TEMPERATURE_OUT2,
		PARAM_HEATER_POWER_OUT2,
		PARAM_ANZ_PARAMS											// 76 - muss immer letzter PARAM sein, wegen Gesamtanzahl		
	};

extern uint32_t P[8]={0};

void collect_data(void);


#endif