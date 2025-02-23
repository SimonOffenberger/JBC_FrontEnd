#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void ButtonUPClicked();
    virtual void ButtonDownClicked();
    virtual void SetNewCurrTemp(int SetTemp);
    virtual void SetNewCurrPower(int Power);
protected:
    int tickCounter;
    int SetTemp = 350;

    void handleTickEvent();
    virtual void sliderValueChanged(int value);
};

#endif // MAINVIEW_HPP
