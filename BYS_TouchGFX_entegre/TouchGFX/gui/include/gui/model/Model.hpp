#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
protected:
    ModelListener* modelListener;
    float CellVoltage1;
    float CellVoltage2;
    float CellVoltage3;
    float CellVoltage4;
    float CellVoltage5;
    float CellVoltage6;
    float CellVoltage7 ;
    float CellVoltage8 ;
    float CellVoltage9 ;
    float CellVoltage10 ;
    float CellVoltage11 ;
    float CellVoltage12 ;
    float CellVoltage13 ;
    float CellVoltage14 ;
    float CellVoltage15 ;
    float CellVoltage16 ;
    float cellVoltagetotal;
    int cellVoltageMaxDiff;
    float cellTempTS1;
	float cellTempTS3;
	float cellTempHDQ;
	float cellTempCFETOFF;
	float bmsFetTemp;
	int packChargeCurrent, packDischargeCurrent, SoCval, SoHval, capacityIntro1;
	float packVoltagee;
	int FetState, BalanceState, SafetyA, SafetyB;


	int loaddetection;
};

#endif // MODEL_HPP
