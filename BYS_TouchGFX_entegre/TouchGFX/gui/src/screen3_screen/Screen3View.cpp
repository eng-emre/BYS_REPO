#include <gui/screen3_screen/Screen3View.hpp>

Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

void Screen3View::set23Value(int val)			//chargecrnt
{
	Unicode::snprintf(ChargeCurrent1Buffer, CHARGECURRENT1_SIZE, "%d", val);
	ChargeCurrent1.invalidate();
}
void Screen3View::set24Value(int val)			//dischargecrnt
{
	Unicode::snprintf(DischargeCurrent1Buffer, DISCHARGECURRENT1_SIZE, "%d", val);
	DischargeCurrent1.invalidate();
}

void Screen3View::set18Value(int val)			//celldiff
{
	Unicode::snprintf(MaxVcellDiff1Buffer, MAXVCELLDIFF1_SIZE, "%d", val);
	MaxVcellDiff1.invalidate();
}

void Screen3View::setFetStateValue(int val) 		//chg pdsg dsg fet states
{
	 //0x1  0. bit (CHG FET)
	 //0x4  2. bit (DSG FET)
	 //0x8  3. bit (Pre-Discharge FET)

	if(val & 0x1)
	{
	     Unicode::snprintf(chgFetState1Buffer, CHGFETSTATE1_SIZE, "ACIK");
	}
	else {
		 Unicode::snprintf(chgFetState1Buffer, CHGFETSTATE1_SIZE, "KAPALI");
	}
	if(val & 0x4)
		{
		 Unicode::snprintf(dsgFetState1Buffer, DSGFETSTATE1_SIZE, "ACIK");
		}
	else {
		Unicode::snprintf(dsgFetState1Buffer, DSGFETSTATE1_SIZE, "KAPALI");
		}
	if(val & 0x8)
		{
		Unicode::snprintf(pdsgFetState1Buffer, PDSGFETSTATE1_SIZE, "ACIK");
		}
	else {
		Unicode::snprintf(pdsgFetState1Buffer, PDSGFETSTATE1_SIZE, "KAPALI");
		}


chgFetState1.invalidate(); // UI'yı güncelle
dsgFetState1.invalidate(); // UI'yı güncelle
pdsgFetState1.invalidate(); // UI'yı güncelle
}


void Screen3View::setloadvalue(int val)			//ld
{


	const int threshold_voltage = 4000;

	    if (val > threshold_voltage) {

	        Unicode::snprintf(loadDetect1Buffer, LOADDETECT1_SIZE, "DEVRE DISI");
	    }
	    else if (val == 0 ){
	    	 Unicode::snprintf(loadDetect1Buffer, LOADDETECT1_SIZE, "DEVRE DISI");
	    }
	    else
	    {
	        Unicode::snprintf(loadDetect1Buffer, LOADDETECT1_SIZE, "BAGLI");
	    }

	    // TextArea'yı güncelle

	    loadDetect1.invalidate();
}

void Screen3View::setBalanceStateValue(int val){

	if(val == 4)
	{
		Unicode::snprintf(cellBalancingState1Buffer, CELLBALANCINGSTATE1_SIZE, "ETKIN");
	}
	else
	{
		Unicode::snprintf(cellBalancingState1Buffer, CELLBALANCINGSTATE1_SIZE, "KAPALI");
	}
	cellBalancingState1.invalidate();
}


