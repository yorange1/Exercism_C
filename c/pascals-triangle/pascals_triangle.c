#include "pascals_triangle.h"

#include <stddef.h>
#include <stdlib.h>

void free_triangle(uint8_t **triangle, size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        if (triangle[i] != NULL)
        {
            free(triangle[i]);
        }
    }

    free(triangle);
}

uint8_t **create_triangle(size_t rows)
{
    uint8_t **triangle = NULL;

    if (rows < 1)
    {
        triangle = (uint8_t **)calloc(1, sizeof(uint8_t *));
        if (NULL == triangle)
        {
            return NULL;
        }

        triangle[0] = (uint8_t *)calloc(1, sizeof(uint8_t));
        if (NULL == triangle[0])
        {
            free_triangle(triangle, 1);
            return NULL;
        }

        return triangle;
    }

    triangle = (uint8_t **)calloc(rows, sizeof(uint8_t *));
    if (NULL == triangle)
    {
        return NULL;
    }

    for (size_t row = 0; row < rows; row++)
    {
        size_t row_len = row + 1;
        triangle[row] = (uint8_t *)calloc(rows, sizeof(uint8_t));
        if (NULL == triangle[row])
        {
            free_triangle(triangle, rows);
            return NULL;
        }

        triangle[row][0] = 1;

        if (row >= 1)
        {
            triangle[row][row_len - 1] = 1;
            for (size_t i = 1; i < row_len - 1; i++)
            {
                triangle[row][i] = triangle[row - 1][i - 1] + triangle[row - 1][i];
            }
        }
    }

    return triangle;
}
