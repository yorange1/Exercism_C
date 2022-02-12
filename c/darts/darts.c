#include "darts.h"

#include <math.h>

#define INNER_CIRCLE_RADIUS (1.0)
#define MIDDLE_CIRCLE_RADIUS (5.0)
#define OUTER_CIRCLE_RADIUS (10.0)

uint8_t score(coordinate_t landing_position)
{
    float dist = hypotf(landing_position.x, landing_position.y);

    if (dist <= INNER_CIRCLE_RADIUS)
    {
        return 10;
    }
    else if (dist <= MIDDLE_CIRCLE_RADIUS)
    {
        return 5;
    }
    else if (dist <= OUTER_CIRCLE_RADIUS)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}