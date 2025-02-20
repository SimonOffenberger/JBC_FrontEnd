#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern "C"{
#include "jbc_powermodul.h"
}


Model::Model() : modelListener(0)
{

}

void Model::tick()
{
  modelListener->SetNewCurrTemp(P[PARAM_ACTUAL_TEMPERATURE_OUT1]);  
}

void Model::setNewSetTemp(int newSetTemp)
{
  set_new_OUT_Temp(newSetTemp);
}
