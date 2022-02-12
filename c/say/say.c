#define _GNU_SOURCE
#include "say.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_INPUT (0)
#define MAX_INPUT (999999999999)
#define MAX_SCALE_NAME_LEN (10)
#define MAX_DIGIT_NAME_LEN (20)
#define MAX_TENS_NAME_LEN (10)
#define SCALE_BASE (1000)

static const char digit_0_19_name[][MAX_DIGIT_NAME_LEN] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

static const char tens_20_90_name[][MAX_TENS_NAME_LEN] = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

static char *say_thousand(uint16_t number)
{
    assert(number < 1000);

    char *under_hundred_str = NULL;
    char *hundred_str = NULL;

    uint16_t hundred = number / 100;
    uint16_t under_hundred = number % 100;

    if (hundred != 0)
    {
        asprintf(&hundred_str, "%s hundred", digit_0_19_name[hundred]);
    }

    if (under_hundred != 0)
    {
        if (under_hundred < 20)
        {
            asprintf(&under_hundred_str, "%s", digit_0_19_name[under_hundred]);
        }
        else
        {
            uint16_t ten = under_hundred / 10;
            uint16_t under_ten = under_hundred % 10;
            if (under_ten != 0)
            {
                asprintf(&under_hundred_str, "%s-%s", tens_20_90_name[ten], digit_0_19_name[under_ten]);
            }
            else
            {
                asprintf(&under_hundred_str, "%s", tens_20_90_name[ten]);
            }
        }
    }

    char *result = NULL;

    if (hundred_str != NULL && under_hundred_str != NULL)
    {
        asprintf(&result, "%s %s", hundred_str, under_hundred_str);
        free(hundred_str);
        free(under_hundred_str);
    }
    else if (hundred_str != NULL)
    {
        result = hundred_str;
    }
    else if (under_hundred_str != NULL)
    {
        result = under_hundred_str;
    }

    return result;
}

int say(int64_t input, char **ans)
{
    assert(ans != NULL);

    if (input > MAX_INPUT || input < MIN_INPUT)
        return -1;

    if (input == 0)
    {
        asprintf(ans, "zero");
        return 0;
    }

    uint16_t under_thousand = input % SCALE_BASE;
    char *under_thousand_str = NULL;
    if (under_thousand != 0)
    {
        under_thousand_str = say_thousand(under_thousand);
    }
    input /= SCALE_BASE;

    uint16_t under_million = input % SCALE_BASE;
    char *under_million_str = NULL;
    if (under_million != 0)
    {
        char *tmp = say_thousand(under_million);
        if (under_thousand_str != NULL)
        {
            asprintf(&under_million_str, "%s thousand %s", tmp, under_thousand_str);
            free(under_thousand_str);
            free(tmp);
        }
        else
        {
            asprintf(&under_million_str, "%s thousand", tmp);
            free(tmp);
        }
    }
    else
    {
        under_million_str = under_thousand_str;
    }
    input /= SCALE_BASE;

    uint16_t under_billion = input % SCALE_BASE;
    char *under_billion_str = NULL;
    if (under_billion != 0)
    {
        char *tmp = say_thousand(under_billion);
        if (under_million_str != NULL)
        {
            asprintf(&under_billion_str, "%s million %s", tmp, under_million_str);
            free(under_million_str);
            free(tmp);
        }
        else
        {
            asprintf(&under_billion_str, "%s million", tmp);
            free(tmp);
        }
    }
    else
    {
        under_billion_str = under_million_str;
    }
    input /= SCALE_BASE;

    uint16_t under_trillion = input % SCALE_BASE;
    char *under_trillion_str = NULL;
    if (under_trillion != 0)
    {
        char *tmp = say_thousand(under_trillion);
        if (under_billion_str != NULL)
        {
            asprintf(&under_trillion_str, "%s billion %s", tmp, under_billion_str);
            free(under_billion_str);
            free(tmp);
        }
        else
        {
            asprintf(&under_trillion_str, "%s billion", tmp);
            free(tmp);
        }
    }
    else
    {
        under_trillion_str = under_billion_str;
    }

    *ans = under_trillion_str;

    return 0;
}
