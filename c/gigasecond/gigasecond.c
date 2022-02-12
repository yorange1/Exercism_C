#include "gigasecond.h"

time_t gigasecond_after(time_t now)
{
    return (time_t)(now + 1000000000);
}
