#include <gui/screen5_screen/Screen5View.hpp>

Screen5View::Screen5View()
{

}

void Screen5View::setupScreen()
{
    Screen5ViewBase::setupScreen();
}

void Screen5View::tearDownScreen()
{
    Screen5ViewBase::tearDownScreen();
}

void Screen5View::set28Value(int val)
{
	Unicode::snprintf(IntroCapacity1Buffer, INTROCAPACITY1_SIZE, "%d", val);
	IntroCapacity1.invalidate();
}

void Screen5View::setcircleProgressValue(int val)
{
	circleProgress1.setValue(val);
}
