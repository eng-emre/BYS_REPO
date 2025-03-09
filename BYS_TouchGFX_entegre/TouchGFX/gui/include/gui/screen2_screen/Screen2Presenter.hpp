#ifndef SCREEN2PRESENTER_HPP
#define SCREEN2PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen2View;

class Screen2Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen2Presenter(Screen2View& v);

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

    virtual ~Screen2Presenter() {}

    virtual void set19Value(float val);		//cellTempTS1
    virtual void set20Value(float val);		//cellTempTS3
    virtual void set21Value(float val);		//cellTempHDQ
    virtual void set22Value(float val);		//cellTempCFETOFF


private:
    Screen2Presenter();

    Screen2View& view;
};

#endif // SCREEN2PRESENTER_HPP
