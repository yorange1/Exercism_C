#ifndef REACT_H
#define REACT_H

#define MAX_CELL_CALLBACKS_NUM (5)
#define MAX_CELL_INPUT (2)
#define MAX_CELL_OUTPUT (5)

typedef enum
{
    INPUT = 0,
    COMPUTE1,
    COMPUTE2
} cell_type;

typedef int (*compute1)(int);
typedef int (*compute2)(int, int);

typedef void (*callback)(void *, int);
typedef int callback_id;

typedef struct reactor
{
    struct cell *cells_head;
    struct cell *cells_tail;
} reactor_t;

typedef struct compute_callback
{
    int cell_value;

    void *info;
    callback func;
} compute_callback_t;

typedef struct cell
{
    struct cell *next;

    cell_type type;

    int value;

    struct cell *inputs[MAX_CELL_INPUT];
    struct cell *output[MAX_CELL_OUTPUT];

    union
    {
        compute1 func1;
        compute2 func2;
    } compute;

    compute_callback_t callbacks[MAX_CELL_CALLBACKS_NUM];

} cell_t;

struct reactor *create_reactor();
// destroy_reactor should free all cells created under that reactor.
void destroy_reactor(struct reactor *);

struct cell *create_input_cell(struct reactor *, int initial_value);
struct cell *create_compute1_cell(struct reactor *, struct cell *, compute1);
struct cell *create_compute2_cell(struct reactor *, struct cell *,
                                  struct cell *, compute2);

int get_cell_value(struct cell *);
void set_cell_value(struct cell *, int new_value);

// The callback should be called with the same void * given in add_callback.
callback_id add_callback(struct cell *, void *, callback);
void remove_callback(struct cell *, callback_id);

#endif
