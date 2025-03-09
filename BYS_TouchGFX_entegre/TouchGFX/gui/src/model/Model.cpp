#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>




#ifndef SIMULATOR

#include "main.h"


extern "C"
{
		extern float cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8 ,cell9, cell10, cell11, cell12, cell13, cell14, cell15, cell16;
		extern float totalcell,   packVoltage, temperatureTS1, temperatureTS3, temperatureHDQ, temperatureCFETOFF, temperatureMosfet;
		extern int capacityIntro, chargeCurrent, dischargeCurrent, SoCstate, SoHstate, loadDetectVoltage, maxCellDiff;
		extern uint8_t FET_Status, value_SafetyStatusA, value_SafetyStatusB;	//chg dsg pdsg fetleri ve koruma tetiklemeleri voltaj sıcaklık...
		extern uint16_t cellBalancingStatus;
}


#endif

Model::Model() : modelListener(0), CellVoltage1{0}
{

}

void Model::tick()
{
#ifndef SIMULATOR



	CellVoltage1 = cell1;
	CellVoltage2 = cell2;
	CellVoltage3 = cell3;
	CellVoltage4 = cell4;
	CellVoltage5 = cell5;
	CellVoltage6 = cell6;
	CellVoltage7 = cell7;
	CellVoltage8 = cell8;
	CellVoltage9 = cell9;
	CellVoltage10 = cell10;
	CellVoltage11 = cell11;
	CellVoltage12 = cell12;
	CellVoltage13 = cell13;
	CellVoltage14 = cell14;
	CellVoltage15 = cell15;
	CellVoltage16 = cell16;
	cellVoltagetotal= totalcell;
	cellVoltageMaxDiff = maxCellDiff;
	cellTempTS1 = temperatureTS1;
	cellTempTS3 = temperatureTS3;
	cellTempHDQ = temperatureHDQ;
	cellTempCFETOFF = temperatureCFETOFF;
	packChargeCurrent = chargeCurrent;
	packDischargeCurrent = dischargeCurrent;
	bmsFetTemp= temperatureMosfet;
	SoCval = SoCstate;
	SoHval = SoHstate;
	capacityIntro1 = capacityIntro;
	packVoltagee = packVoltage;
	loaddetection = loadDetectVoltage;
	FetState = FET_Status;
	BalanceState = cellBalancingStatus;
	SafetyA = value_SafetyStatusA;
	SafetyB = value_SafetyStatusB;


#endif

	modelListener->set1Value(CellVoltage1);
	modelListener->set2Value(CellVoltage2);
	modelListener->set3Value(CellVoltage3);
	modelListener->set4Value(CellVoltage4);
	modelListener->set5Value(CellVoltage5);
	modelListener->set6Value(CellVoltage6);
	modelListener->set7Value(CellVoltage7);
	modelListener->set8Value(CellVoltage8);
	modelListener->set9Value(CellVoltage9);
	modelListener->set10Value(CellVoltage10);
	modelListener->set11Value(CellVoltage11);
	modelListener->set12Value(CellVoltage12);
	modelListener->set13Value(CellVoltage13);
	modelListener->set14Value(CellVoltage14);
	modelListener->set15Value(CellVoltage15);
	modelListener->set16Value(CellVoltage16);
	modelListener->set17Value(cellVoltagetotal);
	modelListener->set18Value(cellVoltageMaxDiff);
	modelListener->set19Value(cellTempTS1);
	modelListener->set20Value(cellTempTS3);
	modelListener->set21Value(cellTempHDQ);
	modelListener->set22Value(cellTempCFETOFF);
	modelListener->set23Value(packChargeCurrent);
	modelListener->set24Value(packDischargeCurrent);

	modelListener->set26Value(SoCval);
	modelListener->set27Value(SoHval);
	modelListener->set28Value(capacityIntro1);
	modelListener->setcircleProgressValue(capacityIntro1);
	modelListener->set29Value(packVoltagee);
	modelListener->setloadvalue(loaddetection);
	modelListener->setFetStateValue(FetState);
	modelListener->setBalanceStateValue(BalanceState);
	modelListener->setSafetyAstateValue(SafetyA);
	modelListener->setSafetyBstateValue(SafetyB);


	HAL_Delay(5);
}
