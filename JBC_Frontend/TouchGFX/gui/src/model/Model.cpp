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
  modelListener->SetNewCurrTemp(P[4]/10);  
  modelListener->SetNewCurrPower(P[5]);
}

void Model::setNewSetTemp(int newSetTemp)
{
  P[3] = newSetTemp*10;
}
