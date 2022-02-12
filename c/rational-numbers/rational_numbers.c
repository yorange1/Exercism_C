#include "rational_numbers.h"

#include <math.h>

#include <stdlib.h>
#include <stdbool.h>

#define is_even(x) ((x & 1) == 0)

static uint16_t gcd(int a, int b)
{
    bool is_even_a = is_even(a);
    bool is_even_b = is_even(b);

    if (is_even_a && is_even_b)
    {   // 都是偶数
        return 2 * gcd(a >> 1, b >> 1);
    }
    else if (is_even_a)
    {   // a是偶数
        return gcd(a >> 1, b);
    }
    else if (is_even_b)
    {   // b是偶数
        return gcd(a, b >> 1);
    }
    else
    {   // 都是奇数
        if (a == b)
        {
            return a;
        }
        else
        {
            return a > b ? gcd(a - b, b) : gcd(a, b - a);
        }
    }
}

rational_t add(rational_t r1, rational_t r2)
{
    rational_t ret = {0};

    ret.numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
    ret.denominator = r1.denominator * r2.denominator;

    ret = reduce(ret);

    return ret;
}

rational_t subtract(rational_t r1, rational_t r2)
{
    rational_t ret = {0};

    ret.numerator = r1.numerator * r2.denominator - r2.numerator * r1.denominator;
    ret.denominator = r1.denominator * r2.denominator;

    ret = reduce(ret);

    return ret;
}

rational_t multiply(rational_t r1, rational_t r2)
{
    rational_t ret = {0, 1};
    if (r1.numerator == 0 || r2.numerator == 0)
    {
        return ret;
    }

    ret.numerator = r1.numerator * r2.numerator;
    ret.denominator = r1.denominator * r2.denominator;

    ret = reduce(ret);

    return ret;
}

rational_t divide(rational_t r1, rational_t r2)
{
    rational_t ret = {0};

    ret.numerator = r1.numerator * r2.denominator;
    ret.denominator = r1.denominator * r2.numerator;
    
    ret = reduce(ret);

    return ret;
}

rational_t absolute(rational_t r)
{
    rational_t ret = {0};

    ret.numerator = abs(r.numerator);
    ret.denominator = abs(r.denominator);

    return ret;
}

rational_t reduce(rational_t r)
{
    rational_t ret = {0, 1};

    if (r.numerator == 0)
    {
        return ret;
    }
    
    rational_t abs_r = absolute(r);

    uint16_t gcd_n = gcd(abs_r.numerator, abs_r.denominator);

    ret.numerator = r.numerator / gcd_n;
    ret.denominator = r.denominator / gcd_n;

    if (ret.denominator < 0)
    {
        ret.denominator *= -1;
        ret.numerator *= -1;
    }

    return ret;
}

rational_t exp_rational(rational_t r, uint16_t n)
{
    rational_t ret = {0};

    ret.numerator = (int)pow(r.numerator, (float)n);
    ret.denominator = (int)pow(r.denominator, (float)n);

    ret = reduce(ret);

    return ret;
}

float exp_real(uint16_t x, rational_t r)
{
    return pow(pow(x, (float)r.numerator), (float)1.0 / r.denominator);
}