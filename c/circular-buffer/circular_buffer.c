#include "circular_buffer.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

circular_buffer_t *new_circular_buffer(size_t capacity)
{
    circular_buffer_t *buffer =
        (circular_buffer_t *)calloc(1, sizeof(circular_buffer_t) + capacity * sizeof(buffer_value_t));
    if (NULL == buffer)
    {
        return NULL;
    }

    buffer->capacity = capacity;
    buffer->write_pos = 0;
    buffer->read_pos = 0;
    buffer->count = 0;

    return buffer;
}

void delete_buffer(circular_buffer_t *buffer)
{
    free(buffer);
}

void clear_buffer(circular_buffer_t *buffer)
{
    memset(buffer->buff, 0, buffer->capacity * sizeof(buffer_value_t));

    buffer->read_pos = 0;
    buffer->write_pos = 0;
    buffer->count = 0;
}

int16_t read(circular_buffer_t *buffer, buffer_value_t *read_value)
{
    if (buffer->count == 0)
    {
        errno = ENODATA;
        return EXIT_FAILURE;
    }

    *read_value = buffer->buff[buffer->read_pos];

    buffer->read_pos = (buffer->read_pos + 1) % buffer->capacity;
    buffer->count--;

    return EXIT_SUCCESS;
}

int16_t write(circular_buffer_t *buffer, buffer_value_t write_value)
{
    if (buffer->count == buffer->capacity)
    {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }

    buffer->buff[buffer->write_pos] = write_value;

    buffer->write_pos = (buffer->write_pos + 1) % buffer->capacity;
    buffer->count++;

    return EXIT_SUCCESS;
}

int16_t overwrite(circular_buffer_t *buffer, buffer_value_t write_value)
{
    buffer->buff[buffer->write_pos] = write_value;

    buffer->write_pos = (buffer->write_pos + 1) % buffer->capacity;

    if (buffer->count != buffer->capacity)
    {
        buffer->count++;
    }
    else
    {
        buffer->read_pos = (buffer->read_pos + 1) % buffer->capacity;
    }

    return EXIT_SUCCESS;
}