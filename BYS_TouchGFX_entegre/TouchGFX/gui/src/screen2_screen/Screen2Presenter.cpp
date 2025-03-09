#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View& v)
    : view(v)
{

}

void Screen2Presenter::activate()
{

}

void Screen2Presenter::deactivate()
{

}


void Screen2Presenter::set19Value(float val)
{
	view.set19Value(val);
}
void Screen2Presenter::set20Value(float val)
{
	view.set20Value(val);
}
void Screen2Presenter::set21Value(float val)
{
	view.set21Value(val);
}
void Screen2Presenter::set22Value(float val)
{
	view.set22Value(val);
}

