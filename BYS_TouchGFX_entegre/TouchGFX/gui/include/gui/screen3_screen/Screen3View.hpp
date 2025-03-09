#ifndef SCREEN3VIEW_HPP
#define SCREEN3VIEW_HPP

#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

class Screen3View : public Screen3ViewBase
{
public:
    Screen3View();
    virtual ~Screen3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void set23Value(int val);		//packChargeCurrent
    virtual void set24Value(int val);		//packDishargeCurrent
    virtual void set18Value(int val);		//cell diff
    virtual void setloadvalue(int val);		//ld pin voltage
    virtual void setFetStateValue(int val); //fet states pdsg dsg chg stored in fet status variable
    virtual void setBalanceStateValue(int val);			//cell balancing state


protected:
};

#endif // SCREEN3VIEW_HPP
