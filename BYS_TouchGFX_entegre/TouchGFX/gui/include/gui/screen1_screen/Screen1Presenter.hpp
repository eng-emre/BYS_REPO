#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

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

    virtual ~Screen1Presenter() {}

    virtual void set1Value(float val);
    virtual void set2Value(float val);
    virtual void set3Value(float val);
    virtual void set4Value(float val);
    virtual void set5Value(float val);
    virtual void set6Value(float val);
    virtual void set7Value(float val);
    virtual void set8Value(float val);
    virtual void set9Value(float val);
    virtual void set10Value(float val);
    virtual void set11Value(float val);
    virtual void set12Value(float val);
    virtual void set13Value(float val);
    virtual void set14Value(float val);
    virtual void set15Value(float val);
    virtual void set16Value(float val);
    virtual void set17Value(float val);
    virtual void set29Value(float val);		//pack+ voltage

private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
