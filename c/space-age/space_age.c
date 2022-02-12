#include "space_age.h"

#define EARTH_SECONDS_PER_YEAR (31557600.0)

float age(planet_t planet, int64_t seconds)
{
    if (planet < MERCURY || planet > NEPTUNE)
    {
        return -1.0;
    }

    float orbital_period[] = {0.2408467, 0.61519726, 1.0, 1.8808158, 11.862615, 29.447498, 84.016846, 164.79132};

    return (float)seconds / (EARTH_SECONDS_PER_YEAR * orbital_period[planet]);
}
