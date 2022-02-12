#include "square_root.h"

#include <stdbool.h>
#include <math.h>

uint16_t square_root(uint16_t number)
{
    if (0 == number)
    {
        return 0;
    }
    
    double C = number, x0 = number;

    while (true)
    {
        double xi = 0.5 * (x0 + C / x0);
        if (fabs(x0 - xi) < 1e-7)
        {
            break;
        }
        
        x0 = xi;
    }
    
    return (uint16_t)x0;
}