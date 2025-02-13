#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern "C"{
#include "jbc_powermodul.h"
extern uint32_t P[8];
}


Model::Model() : modelListener(0)
{

}

void Model::tick()
{
  modelListener->SetNewCurrTemp(P[4]);  
}

void Model::setNewSetTemp(int newSetTemp)
{
}
