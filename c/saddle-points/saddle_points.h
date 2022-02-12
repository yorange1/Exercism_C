#ifndef SADDLE_POINTS_H
#define SADDLE_POINTS_H

#include <stddef.h>
#include <stdint.h>

typedef struct saddle_point
{
    size_t row;
    size_t column;
} saddle_point_t;

typedef struct saddle_points
{
    size_t count;
    saddle_point_t points[];
} saddle_points_t;

saddle_points_t *saddle_points(size_t row_num, size_t col_num, const void *matrix);
void free_saddle_points(saddle_points_t *points);

#endif
