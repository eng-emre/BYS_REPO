#include <gui/screen4_screen/Screen4View.hpp>

Screen4View::Screen4View()
{

}

void Screen4View::setupScreen()
{
    Screen4ViewBase::setupScreen();
}

void Screen4View::tearDownScreen()
{
    Screen4ViewBase::tearDownScreen();
}


void Screen4View::setSafetyAstateValue(int val){

	uint8_t CUV, COV, OCC, OCD, SCD;



			CUV = ((val & 0x04)>>2);			//2.bit cuv 2 bit shift edildi ve yazdırıldı bitwise extractiondan sonra  safety alarm a register
			COV = ((val & 0x08)>>3);			//3.bit cov
			OCC = ((val & 0x10)>>4);			//4.bit occ
			OCD = ((val & 0x20)>>5);			//5.bit ocd
			SCD = ((val & 0x80)>>7);			//6.bit scd

			Unicode::snprintf(cellUnderVoltage1Buffer, CELLUNDERVOLTAGE1_SIZE, "%u", CUV);
			Unicode::snprintf(cellOverVoltage1Buffer, CELLOVERVOLTAGE1_SIZE, "%u", COV);
			Unicode::snprintf(overCurrentCharge1Buffer, OVERCURRENTCHARGE1_SIZE, "%u", OCC);
			Unicode::snprintf(overCurrentDischargeBuffer, OVERCURRENTDISCHARGE_SIZE, "%u", OCD);
			Unicode::snprintf(shortCircuitChargeBuffer, SHORTCIRCUITCHARGE_SIZE, "%u", SCD);




		cellUnderVoltage1.invalidate();
		cellOverVoltage1.invalidate();
		overCurrentCharge1.invalidate();
		overCurrentDischarge.invalidate();
		shortCircuitCharge.invalidate();

}
void Screen4View::setSafetyBstateValue(int val){
	uint8_t OTC, UTC, OTD, UTD, OTINT, UTINT;

			UTC = ((val & 0x01)>>0);			//0.bit UTC
			UTD = ((val & 0x02)>>1);			//1.bit UTD
			UTINT = ((val & 0x04)>>2);			//2.bit UTINT

			//3.bit reserved

			OTC = ((val & 0x10)>>4);			//4.bit OTC		safety alarm b register
			OTD = ((val & 0x20)>>5);			//5.bit OTD
			OTINT = ((val & 0x40)>>6);			//6.bit OTINT


			Unicode::snprintf(underTempCharge1Buffer, UNDERTEMPCHARGE1_SIZE, "%u", UTC);
			Unicode::snprintf(underTempDischarge1Buffer, UNDERTEMPDISCHARGE1_SIZE, "%u", UTD);
			Unicode::snprintf(underTempInternal1Buffer, UNDERTEMPINTERNAL1_SIZE, "%u", UTINT);
			Unicode::snprintf(overTempCharge1Buffer, OVERTEMPCHARGE1_SIZE, "%u", OTC);
			Unicode::snprintf(overTempDischarge1Buffer, OVERTEMPDISCHARGE1_SIZE, "%u", OTD);
			Unicode::snprintf(overTempInternal1Buffer, OVERTEMPINTERNAL1_SIZE, "%u", OTINT);

			underTempCharge1.invalidate();
			underTempDischarge1.invalidate();
			underTempInternal1.invalidate();
			overTempCharge1.invalidate();
			overTempDischarge1.invalidate();
			overTempInternal1.invalidate();


}
