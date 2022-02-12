#include "palindrome_products.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_palindrome(int number)
{
    int sum = 0;
    int temp = number;

    while (temp != 0)
    {
        int r = temp % 10;
        sum = sum * 10 + r;
        temp /= 10;
    }

    return (sum == number);
}

static void init_factors(factor_t **factors, int a, int b)
{
    assert(factors != NULL);

    *factors = (factor_t *)calloc(1, sizeof(factor_t));

    (*factors)->factor_a = a;
    (*factors)->factor_b = b;
}

static void insert_factors(factor_t *factors, int a, int b)
{
    factor_t *tail = factors;

    while (tail->next != NULL)
    {
        tail = tail->next;
    }

    tail->next = (factor_t *)calloc(1, sizeof(factor_t));
    assert(tail->next != NULL);

    tail->next->factor_a = a;
    tail->next->factor_b = b;
}

static void free_factors(factor_t *factors)
{
    assert(factors != NULL);

    factor_t *next = factors->next;
    while (next != NULL)
    {
        factor_t *temp = next;
        next = next->next;

        free(temp);
    }

    free(factors);
}

product_t *get_palindrome_product(int from, int to)
{
    product_t *product = (product_t *)calloc(1, sizeof(product_t));
    assert(product != NULL);

    if (from > to)
    {
        snprintf(product->error, MAXERR, "invalid input: min is %d and max is %d", from, to);
        return product;
    }

    // Find the largest and smallest palindromes
    for (int i = from; i <= to; i++)
    {
        for (int j = i; j <= to; j++)
        {
            int candidate = i * j;
            if (is_palindrome(candidate))
            {
                if (0 == product->smallest && 0 == product->largest)
                {
                    // first palindrome
                    product->smallest = candidate;
                    product->largest = candidate;
                    init_factors(&product->factors_sm, i, j);
                    init_factors(&product->factors_lg, i, j);
                }
                else if (candidate == product->smallest)
                {
                    insert_factors(product->factors_sm, i, j);
                }
                else if (candidate == product->largest)
                {
                    insert_factors(product->factors_lg, i, j);
                }
                else if (candidate > product->largest)
                {
                    free_factors(product->factors_lg);
                    init_factors(&product->factors_lg, i, j);
                    product->largest = candidate;
                }
            }
        }
    }

    if (product->smallest == 0)
    {
        snprintf(product->error, MAXERR, "no palindrome with factors in the range %d to %d", from, to);
    }

    return product;
}

void free_product(product_t *p)
{
    assert(p != NULL);

    if (p->factors_lg != NULL)
    {
        free_factors(p->factors_lg);
    }

    if (p->factors_sm != NULL)
    {
        free_factors(p->factors_sm);
    }

    free(p);
}
