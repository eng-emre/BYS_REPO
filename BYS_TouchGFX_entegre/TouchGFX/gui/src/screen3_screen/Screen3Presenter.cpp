#include <gui/screen3_screen/Screen3View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

Screen3Presenter::Screen3Presenter(Screen3View& v)
    : view(v)
{

}

void Screen3Presenter::activate()
{

}

void Screen3Presenter::deactivate()
{

}

void Screen3Presenter::set23Value(int val)
{
	view.set23Value(val);
}
void Screen3Presenter::set24Value(int val)
{
	view.set24Value(val);
}
void Screen3Presenter::set18Value(int val)
{
	view.set18Value(val);
}
void Screen3Presenter::setloadvalue(int val)
{
	view.setloadvalue(val);
}
void Screen3Presenter::setFetStateValue(int val)
{
	view.setFetStateValue(val);
}
void Screen3Presenter::setBalanceStateValue(int val)
{
	view.setBalanceStateValue(val);
}
