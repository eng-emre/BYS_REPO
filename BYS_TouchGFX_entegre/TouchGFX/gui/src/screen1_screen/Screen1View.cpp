#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}


void Screen1View::set1Value(float val)
{
	Unicode::snprintfFloat(Vcell1Buffer, VCELL1_SIZE, "%.3f", val);
	Vcell1.invalidate();
}
void Screen1View::set2Value(float val)
{
	Unicode::snprintfFloat(Vcell2Buffer, VCELL2_SIZE, "%.3f", val);
	Vcell2.invalidate();
}
void Screen1View::set3Value(float val)
{
	Unicode::snprintfFloat(Vcell3Buffer, VCELL3_SIZE, "%.3f", val);
	Vcell3.invalidate();
}
void Screen1View::set4Value(float val)
{
	Unicode::snprintfFloat(Vcell4Buffer, VCELL4_SIZE, "%.3f", val);
	Vcell4.invalidate();
}
void Screen1View::set5Value(float val)
{
	Unicode::snprintfFloat(Vcell5Buffer, VCELL5_SIZE, "%.3f", val);
	Vcell5.invalidate();
}
void Screen1View::set6Value(float val)
{
	Unicode::snprintfFloat(Vcell6Buffer, VCELL6_SIZE, "%.3f", val);
	Vcell6.invalidate();
}
void Screen1View::set7Value(float val)
{
	Unicode::snprintfFloat(Vcell7Buffer, VCELL7_SIZE, "%.3f", val);
	Vcell7.invalidate();
}
void Screen1View::set8Value(float val)
{
	Unicode::snprintfFloat(Vcell8Buffer, VCELL8_SIZE, "%.3f", val);
	Vcell8.invalidate();
}
void Screen1View::set9Value(float val)
{
	Unicode::snprintfFloat(Vcell9Buffer, VCELL9_SIZE, "%.3f", val);
	Vcell9.invalidate();
}

void Screen1View::set10Value(float val)
{
	Unicode::snprintfFloat(Vcell10Buffer, VCELL10_SIZE, "%.3f", val);
	Vcell10.invalidate();
}
void Screen1View::set11Value(float val)
{
	Unicode::snprintfFloat(Vcell11Buffer, VCELL11_SIZE, "%.3f", val);
	Vcell11.invalidate();
}

void Screen1View::set12Value(float val)
{
	Unicode::snprintfFloat(Vcell12Buffer, VCELL12_SIZE, "%.3f", val);
	Vcell12.invalidate();
}
void Screen1View::set13Value(float val)
{
	Unicode::snprintfFloat(Vcell13Buffer, VCELL13_SIZE, "%.3f", val);
	Vcell13.invalidate();
}
void Screen1View::set14Value(float val)
{
	Unicode::snprintfFloat(Vcell14Buffer, VCELL14_SIZE, "%.3f", val);
	Vcell14.invalidate();
}
void Screen1View::set15Value(float val)
{
	Unicode::snprintfFloat(Vcell15Buffer, VCELL15_SIZE, "%.3f", val);
	Vcell15.invalidate();
}
void Screen1View::set16Value(float val)
{
	Unicode::snprintfFloat(Vcell16Buffer, VCELL16_SIZE, "%.3f", val);
	Vcell16.invalidate();
}
void Screen1View::set17Value(float val)
{
	Unicode::snprintfFloat(TotalCellVoltageBuffer, TOTALCELLVOLTAGE_SIZE, "%.3f", val);
	TotalCellVoltage.invalidate();
}
void Screen1View::set29Value(float val)
{
	Unicode::snprintfFloat(PackVoltage1Buffer, PACKVOLTAGE1_SIZE, "%.3f", val);
	PackVoltage1.invalidate();
}





