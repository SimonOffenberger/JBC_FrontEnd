#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}

    virtual ~ModelListener() {}

    virtual void SetNewCurrTemp(int CurrTemp);
    virtual void SetNewCurrPower(int Power);

    void bind(Model* m)
    {
        model = m;
    }
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
