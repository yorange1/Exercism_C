#include "meetup.h"
#include <time.h>
#include <string.h>
static const char *weekdays[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
static const unsigned int days_in_month[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static unsigned int weekday_to_num(const char *weekday)
{
    for (unsigned int i = 0; i < 7; i++)
        if (!strcmp(weekdays[i], weekday))
            return i;
    return 8;
}

static unsigned int is_leap(unsigned int year)
{
    return !(year % 4) && ((year % 100) || !(year % 400));
}

int meetup_day_of_month(unsigned int year,
                        unsigned int month,
                        const char *week,
                        const char *day_of_week)
{
    struct tm tm = {
        .tm_year = year - 1900,
        .tm_mon = month - 1,
        .tm_mday = 1,
    };
    mktime(&tm);
    int wday = weekday_to_num(day_of_week);
    if (wday > 7)
        goto fail;

    int day = 1 + wday - tm.tm_wday;
    if (day <= 0)
        day += 7;

    if (!strcmp(week, "first"))
    {
        return day;
    }
    else if (!strcmp(week, "second"))
    {
        return day + 7;
    }
    else if (!strcmp(week, "third"))
    {
        return day + 14;
    }
    else if (!strcmp(week, "fourth"))
    {
        return day + 21;
    }
    else if (!strcmp(week, "last"))
    {
        int ndays = days_in_month[is_leap(year)][month - 1];
        return (day + 28) > ndays ? day + 21 : day + 28;
    }
    else if (!strcmp(week, "teenth"))
    {
        return (day + 7) < 13 ? day + 14 : day + 7;
    }

fail:
    return -1;
}
