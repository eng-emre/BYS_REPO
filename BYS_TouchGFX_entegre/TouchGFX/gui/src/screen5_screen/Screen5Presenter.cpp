#include <gui/screen5_screen/Screen5View.hpp>
#include <gui/screen5_screen/Screen5Presenter.hpp>

Screen5Presenter::Screen5Presenter(Screen5View& v)
    : view(v)
{

}

void Screen5Presenter::activate()
{

}

void Screen5Presenter::deactivate()
{

}

void Screen5Presenter::set28Value(int val)		//intro capacity
{
	view.set28Value(val);
}

void Screen5Presenter::setcircleProgressValue(int val)
{
	view.setcircleProgressValue(val);
}
