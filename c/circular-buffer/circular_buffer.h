#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stddef.h>
#include <stdint.h>

typedef int buffer_value_t;

typedef struct circular_buffer
{
    size_t capacity;
    size_t count;

    size_t write_pos;
    size_t read_pos;

    buffer_value_t buff[];
} circular_buffer_t;

circular_buffer_t *new_circular_buffer(size_t capacity);
void delete_buffer(circular_buffer_t *buffer);
void clear_buffer(circular_buffer_t *buffer);

int16_t read(circular_buffer_t *buffer, buffer_value_t *read_value);
int16_t write(circular_buffer_t *buffer, buffer_value_t write_value);
int16_t overwrite(circular_buffer_t *buffer, buffer_value_t write_value);

#endif
