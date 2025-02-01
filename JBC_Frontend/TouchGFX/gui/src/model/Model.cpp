#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
  modelListener->SetNewCurrTemp(250);  
}

void Model::setNewSetTemp(int newSetTemp)
{
}
