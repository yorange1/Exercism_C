#include "complex_numbers.h"

#include <math.h>

complex_t c_add(complex_t a, complex_t b)
{
    complex_t result = {
        .real = a.real + b.real,
        .imag = a.imag + b.imag};

    return result;
}

complex_t c_sub(complex_t a, complex_t b)
{
    complex_t result = {
        .real = a.real - b.real,
        .imag = a.imag - b.imag};

    return result;
}

complex_t c_mul(complex_t a, complex_t b)
{
    complex_t result = {
        .real = a.real * b.real - a.imag * b.imag,
        .imag = a.imag * b.real + a.real * b.imag};

    return result;
}

complex_t c_div(complex_t a, complex_t b)
{
    complex_t result = {
        .real = (a.real * b.real + a.imag * b.imag) / (b.real * b.real + b.imag * b.imag),
        .imag = (a.imag * b.real - a.real * b.imag) / (b.real * b.real + b.imag * b.imag)};

    return result;
}

double c_abs(complex_t x)
{
    return sqrt(x.real * x.real + x.imag * x.imag);
}

complex_t c_conjugate(complex_t x)
{
    complex_t result = {
        .real = x.real,
        .imag = -x.imag};

    return result;
}

double c_real(complex_t x)
{
    return x.real;
}

double c_imag(complex_t x)
{
    return x.imag;
}

complex_t c_exp(complex_t x)
{
    complex_t result = {
        .real = exp(x.real) * cos(x.imag),
        .imag = exp(x.real) * sin(x.imag)};

    return result;
}
