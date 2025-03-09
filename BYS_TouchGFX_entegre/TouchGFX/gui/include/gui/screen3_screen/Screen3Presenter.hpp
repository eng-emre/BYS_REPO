#ifndef SCREEN3PRESENTER_HPP
#define SCREEN3PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen3View;

class Screen3Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen3Presenter(Screen3View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen3Presenter() {}

    virtual void set23Value(int val);		//packChargeCurrent
    virtual void set24Value(int val);		//packDishargeCurrent
    virtual void set18Value(int val);		//cellVoltageMaxDiff
    virtual void setloadvalue(int val);		//ld pin voltage
    virtual void setFetStateValue(int val);		//chg pdsg dsg fet states
    virtual void setBalanceStateValue(int val);		//cb state on or off


private:
    Screen3Presenter();

    Screen3View& view;
};

#endif // SCREEN3PRESENTER_HPP
