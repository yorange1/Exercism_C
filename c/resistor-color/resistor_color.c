#include "resistor_color.h"

int color_code(resistor_band_t band)
{
    return (band - BLACK);
}

const resistor_band_t* colors()
{
    static resistor_band_t bands[] = {
        BLACK,
        BROWN,
        RED,
        ORANGE,
        YELLOW,
        GREEN,
        BLUE,
        VIOLET,
        GREY,
        WHITE
    };

    return bands;
}