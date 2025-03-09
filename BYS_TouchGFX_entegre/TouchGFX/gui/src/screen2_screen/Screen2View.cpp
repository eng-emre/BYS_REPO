#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}


void Screen2View::set19Value(float val)
{
	Unicode::snprintfFloat(TempBatt1Buffer, TEMPBATT1_SIZE, "%.1f", val);
	TempBatt1.invalidate();
}
void Screen2View::set20Value(float val)
{
	Unicode::snprintfFloat(TempBatt2Buffer, TEMPBATT2_SIZE, "%.1f", val);
	TempBatt2.invalidate();
}
void Screen2View::set21Value(float val)
{
	Unicode::snprintfFloat(TempBatt3Buffer, TEMPBATT3_SIZE, "%.1f", val);
	TempBatt3.invalidate();
}
void Screen2View::set22Value(float val)
{
	Unicode::snprintfFloat(TempBatt4Buffer, TEMPBATT4_SIZE, "%.1f", val);
	TempBatt4.invalidate();
}
