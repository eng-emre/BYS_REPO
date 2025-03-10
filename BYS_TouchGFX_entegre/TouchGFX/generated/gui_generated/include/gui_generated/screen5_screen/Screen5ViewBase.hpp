/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN5VIEWBASE_HPP
#define SCREEN5VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen5_screen/Screen5Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class Screen5ViewBase : public touchgfx::View<Screen5Presenter>
{
public:
    Screen5ViewBase();
    virtual ~Screen5ViewBase();
    virtual void setupScreen();
    virtual void handleKeyEvent(uint8_t key);

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image image1;
    touchgfx::CircleProgress circleProgress1;
    touchgfx::PainterRGB565 circleProgress1Painter;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea1;
    touchgfx::TextArea textArea3;
    touchgfx::TextAreaWithOneWildcard IntroCapacity1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t INTROCAPACITY1_SIZE = 9;
    touchgfx::Unicode::UnicodeChar IntroCapacity1Buffer[INTROCAPACITY1_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 4800;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

};

#endif // SCREEN5VIEWBASE_HPP
