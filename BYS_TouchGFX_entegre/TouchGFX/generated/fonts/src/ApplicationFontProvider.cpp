/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <fonts/ApplicationFontProvider.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

touchgfx::Font* ApplicationFontProvider::getFont(touchgfx::FontId typography)
{
    switch (typography)
    {
    case Typography::DEFAULT:
        // SCHLBKB_TTF_19_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[0]);
    case Typography::LARGE:
        // verdana_40_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[1]);
    case Typography::SMALL:
        // tahomabd_13_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[2]);
    case Typography::MAINHEADERS:
        // verdanab_15_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[3]);
    case Typography::CELLSANDOTHERS:
        // verdana_13_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[4]);
    case Typography::SUBHEADERS:
        // verdanab_14_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[5]);
    case Typography::TYPOGRAPHY_00:
        // timesi_11_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[6]);
    case Typography::COVERL:
        // tahomabd_15_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[7]);
    case Typography::INTROCAP:
        // verdanab_22_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[8]);
    case Typography::COMMENT:
        // verdana_10_4bpp
        return const_cast<touchgfx::Font*>(TypedTextDatabase::getFonts()[9]);
    default:
        return 0;
    }
}
