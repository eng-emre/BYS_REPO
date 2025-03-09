#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void set19Value(float val);		//cellTempTS1
    virtual void set20Value(float val);		//cellTempTS3
    virtual void set21Value(float val);		//cellTempHDQ
    virtual void set22Value(float val);		//cellTempCFETOFF


protected:
};

#endif // SCREEN2VIEW_HPP
