#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void set1Value(float val) {};		//cell1
    virtual void set2Value(float val) {};		//cell2
    virtual void set3Value(float val) {};		//cell3
    virtual void set4Value(float val) {};		//cell4
    virtual void set5Value(float val) {};		//cell5
    virtual void set6Value(float val) {};		//cell6
    virtual void set7Value(float val) {};		//cell7
    virtual void set8Value(float val) {};		//cell8
    virtual void set9Value(float val) {};		//cell9
    virtual void set10Value(float val) {};		//cell10
    virtual void set11Value(float val) {};		//cell11
    virtual void set12Value(float val) {};		//cell12
    virtual void set13Value(float val) {};		//cell13
    virtual void set14Value(float val) {};		//cell14
    virtual void set15Value(float val) {};		//cell15
    virtual void set16Value(float val) {};		//cell16
    virtual void set17Value(float val) {};		//cellVoltagetotal
    virtual void set18Value(int val) {};		//cellVoltageMaxDiff

    virtual void set19Value(float val) {};		//cellTempTS1
    virtual void set20Value(float val) {};		//cellTempTS3
    virtual void set21Value(float val) {};		//cellTempHDQ
    virtual void set22Value(float val) {};		//cellTempCFETOFF
    virtual void set23Value(int val) {};		//packChargeCurrent
    virtual void set24Value(int val) {};		//packDishargeCurrent

    virtual void set26Value(int val) {};		//SoC
    virtual void set27Value(int val) {};		//SoH
    virtual void set28Value(int val) {};		//capacityIntro
    virtual void setcircleProgressValue(int val) {};	//circle progress
    virtual void set29Value(float val) {};		//pack+ voltage
    virtual void setloadvalue(int val) {};		//ld pin voltage
    virtual void setFetStateValue(int val) {};		//chg pdsg dsg fet states
    virtual void setBalanceStateValue(int val) {};	//balancing state on/off
    virtual void setSafetyAstateValue(int val) {};
    virtual void setSafetyBstateValue(int val) {};



protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
