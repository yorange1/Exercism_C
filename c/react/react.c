#include "react.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

struct reactor *create_reactor()
{
    struct reactor *reactor = (struct reactor *)calloc(1, sizeof(struct reactor));
    assert(reactor != NULL);

    return reactor;
}

void destroy_reactor(struct reactor *reactor)
{
    assert(reactor != NULL);

    for (struct cell *cell = reactor->cells_head; cell != NULL;)
    {
        struct cell *temp = cell;
        cell = cell->next;
        free(temp);
    }

    free(reactor);
}

static void add_cell(struct reactor *reactor, struct cell *cell)
{
    if (NULL == reactor->cells_head)
    {
        reactor->cells_head = cell;
        reactor->cells_tail = cell;
    }
    else
    {
        reactor->cells_tail->next = cell;
        reactor->cells_tail = cell;
    }
}

struct cell *create_input_cell(struct reactor *reactor, int initial_value)
{
    assert(reactor != NULL);

    struct cell *cell = (struct cell *)calloc(1, sizeof(struct cell));
    assert(cell != NULL);

    cell->type = INPUT;

    cell->value = initial_value;

    add_cell(reactor, cell);

    return cell;
}

static void add_output_cell(struct cell *cell, struct cell *output)
{
    size_t i = 0;

    for (; i < MAX_CELL_OUTPUT; i++)
    {
        if (cell->output[i] == NULL)
        {
            cell->output[i] = output;
            break;
        }
    }
    assert(i != MAX_CELL_OUTPUT);
}

struct cell *create_compute1_cell(struct reactor *reactor, struct cell *input_cell, compute1 compute)
{
    assert(reactor != NULL && input_cell != NULL && compute != NULL);

    struct cell *compute_cell = (struct cell *)calloc(1, sizeof(struct cell));
    assert(compute_cell != NULL);

    compute_cell->type = COMPUTE1;

    compute_cell->inputs[0] = input_cell;
    compute_cell->compute.func1 = compute;

    add_output_cell(input_cell, compute_cell);

    compute_cell->value = compute(input_cell->value);

    add_cell(reactor, compute_cell);

    return compute_cell;
}

struct cell *create_compute2_cell(struct reactor *reactor, struct cell *input_cell1,
                                  struct cell *input_cell2, compute2 compute)
{
    assert(reactor != NULL && input_cell1 != NULL && input_cell2 != NULL && compute != NULL);

    struct cell *compute_cell = (struct cell *)calloc(1, sizeof(struct cell));
    assert(compute_cell != NULL);

    compute_cell->type = COMPUTE2;

    compute_cell->inputs[0] = input_cell1;
    compute_cell->inputs[1] = input_cell2;
    compute_cell->compute.func2 = compute;

    add_output_cell(input_cell1, compute_cell);
    add_output_cell(input_cell2, compute_cell);

    compute_cell->value = compute(input_cell1->value, input_cell2->value);

    add_cell(reactor, compute_cell);

    return compute_cell;
}

int get_cell_value(struct cell *cell)
{
    assert(cell != NULL);

    return cell->value;
}

static int compute_value(struct cell *cell)
{
    if (COMPUTE1 == cell->type)
    {
        struct cell *input = cell->inputs[0];
        compute1 func = cell->compute.func1;
        cell->value = func(input->value);
    }
    else if (COMPUTE2 == cell->type)
    {
        struct cell *input1 = cell->inputs[0];
        struct cell *input2 = cell->inputs[1];
        compute2 func = cell->compute.func2;
        cell->value = func(input1->value, input2->value);
    }

    return cell->value;
}

static void update_value(struct cell *cell)
{
    if (cell->type != INPUT)
    {
        int prev_value = cell->value;
        int new_value = compute_value(cell);
        if (new_value == prev_value)
        {
            return;
        }
    }

    for (size_t i = 0; i < MAX_CELL_OUTPUT; i++)
    {
        if (cell->output[i] != NULL)
        {
            update_value(cell->output[i]);
        }
    }
}

static void check_callbacks(struct cell *cell)
{
    if (cell->type != INPUT)
    {
        for (size_t i = 0; i < MAX_CELL_CALLBACKS_NUM; i++)
        {
            compute_callback_t *callback = &cell->callbacks[i];

            if (callback->func != NULL)
            {
                if (cell->value == callback->cell_value)
                {
                    return;
                }

                callback->func(callback->info, cell->value);
                callback->cell_value = cell->value;
            }
        }
    }

    for (size_t i = 0; i < MAX_CELL_OUTPUT; i++)
    {
        if (cell->output[i] != NULL)
        {
            check_callbacks(cell->output[i]);
        }
    }
}

void set_cell_value(struct cell *input_cell, int new_value)
{
    assert(input_cell != NULL && input_cell->type == INPUT);

    input_cell->value = new_value;

    update_value(input_cell);

    check_callbacks(input_cell);
}

callback_id add_callback(struct cell *compute_cell, void *info, callback func)
{
    assert(compute_cell != NULL && compute_cell->type != INPUT);

    struct compute_callback *callbacks = compute_cell->callbacks;

    callback_id id = 0;

    for (; id < MAX_CELL_CALLBACKS_NUM; id++)
    {
        if (callbacks[id].func == NULL)
        {
            callbacks[id].cell_value = compute_cell->value;
            callbacks[id].func = func;
            callbacks[id].info = info;
            break;
        }
    }
    assert(id != MAX_CELL_CALLBACKS_NUM);

    return id;
}

void remove_callback(struct cell *compute_cell, callback_id id)
{
    assert(compute_cell != NULL && compute_cell->type != INPUT);

    struct compute_callback *callbacks = compute_cell->callbacks;

    callbacks[id].func = NULL;
    callbacks[id].info = NULL;
}
