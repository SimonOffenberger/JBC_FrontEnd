#include <gui/main_screen/MainView.hpp>
#include <math.h>
#include <stdlib.h>

static uint16_t randomish(int32_t seed)
{
    static uint16_t last = 0;
    const uint16_t num = (seed * (1337 + last)) % 0xFFFF;
    last = num;
    return num;
}

MainView::MainView()
{
    tickCounter = 0;
}


void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::handleTickEvent()
{
    tickCounter++;

    // Insert each second tick
    if (tickCounter % 2 == 0)
    {
        float yMax = SetPointGraph.getGraphRangeYMaxAsFloat();

        // Insert "random" points along a sine wave
        SetPointGraph.addDataPoint((int)(SetTemp));
        CurrTempGraph.addDataPoint((int)((sinf(tickCounter * .04f) + 1) * (yMax / 2.2f)) + randomish(tickCounter) % (int)(yMax / 10.f));

    }
}

void MainView::sliderValueChanged(int value)
{

    // Adjust the Y-axis max value according to the slider value
    SetPointGraph.setGraphRangeY(0, value);
    SetPointGraph.invalidate();

    // Adjust the interval of the labels/grid lines on the Y-axis
    // to match the new range.
    if (value > 199)
    {
        SetPointGraphMajorYAxisLabel.setInterval(50);
        SetPointGraphMajorYAxisGrid.setInterval(50);
    }
    else if (value > 100)
    {
       SetPointGraphMajorYAxisLabel.setInterval(20);
        SetPointGraphMajorYAxisGrid.setInterval(20);
    }
    else
    {
        SetPointGraphMajorYAxisLabel.setInterval(10);
        SetPointGraphMajorYAxisGrid.setInterval(10);
    }

   SetPointGraphMajorYAxisLabel.invalidate();
   SetPointGraphMajorYAxisGrid.invalidate();
}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();
    // Initialize graph range with default slider value at start up
   // MainView::sliderValueChanged(sliderResolution.getValue());
//    Unicode::snprintf(TextAreaSetPointBuffer, TEXTAREASETPOINT_SIZE, "%s",touchgfx::TypedText(SetTemp).getText());
// TextAreaSetPoint.invalidate();
}

void MainView::ButtonUPClicked(){
    SetTemp += 10;
    Unicode::snprintf(TextAreaSetPointBuffer, TEXTAREASETPOINT_SIZE, "%d",SetTemp);
    TextAreaSetPoint.invalidate();
}

void MainView::ButtonDownClicked(){
    SetTemp -= 10;
    Unicode::snprintf(TextAreaSetPointBuffer, TEXTAREASETPOINT_SIZE, "%d",SetTemp);
    TextAreaSetPoint.invalidate();
}