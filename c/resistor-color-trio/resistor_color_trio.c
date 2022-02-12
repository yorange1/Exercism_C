#include <math.h>
#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t colors[])
{
    uint32_t val = (10 * colors[0] + colors[1]) * pow(10, colors[2]);

    resistor_value_t result = {
        .value = val < 1000 ? val : val / 1000,
        .unit = val < 1000 ? OHMS : KILOOHMS,
    };

    return result;
}