#include "saddle_points.h"

#include <stdlib.h>
#include <string.h>

static uint8_t max_row(size_t row, size_t col_num, const uint8_t *matrix_p)
{
    uint8_t max = matrix_p[row * col_num];

    for (size_t i = 1; i < col_num; i++)
    {
        if (matrix_p[row * col_num + i] > max)
        {
            max = matrix_p[row * col_num + i];
        }
    }

    return max;
}

static uint8_t min_col(size_t col, size_t row_num, size_t col_num, const uint8_t *matrix_p)
{
    uint8_t min = matrix_p[col];

    for (size_t i = 1; i < row_num; i++)
    {
        if (matrix_p[i * col_num + col] < min)
        {
            min = matrix_p[i * col_num + col];
        }
    }

    return min;
}

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix)
{
    uint8_t matrix_flag[row_num][col_num];
    memset(matrix_flag, 0, sizeof(matrix_flag));

    const uint8_t *matrix_p = (const uint8_t *)matrix;

    // Find element greater than or equal to every element in its row.
    for (size_t i = 0; i < row_num; i++)
    {
        uint8_t max = max_row(i, col_num, matrix_p);
        for (size_t j = 0; j < col_num; j++)
        {
            if (matrix_p[i * col_num + j] == max)
            {
                matrix_flag[i][j]++;
            }
        }
    }

    uint8_t count = 0;
    saddle_point_t points_temp[row_num * col_num];

    // Find element less than or equal to every element in its column.
    for (size_t i = 0; i < col_num; i++)
    {
        uint8_t min = min_col(i, row_num, col_num, matrix_p);
        for (size_t j = 0; j < row_num; j++)
        {
            if (matrix_p[j * col_num + i] == min && matrix_flag[j][i] == 1)
            {
                points_temp[count].row = j + 1;
                points_temp[count].column = i + 1;

                count++;
            }
        }
    }

    saddle_points_t *points = (saddle_points_t *)calloc(1, sizeof(saddle_points_t) + count * sizeof(saddle_point_t));
    if (NULL == points)
    {
        return NULL;
    }

    memcpy(points->points, points_temp, count * sizeof(saddle_point_t));
    points->count = count;

    return points;
}

void free_saddle_points(saddle_points_t *points)
{
    free(points);
}
