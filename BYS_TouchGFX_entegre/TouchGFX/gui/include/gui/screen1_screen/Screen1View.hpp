#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

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
    virtual void set29Value(float val);

protected:
};

#endif // SCREEN1VIEW_HPP
