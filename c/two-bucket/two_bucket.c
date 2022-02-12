#include "two_bucket.h"

#include <stdint.h>
#include <stdio.h>

#define is_even(x) ((x & 1) == 0)
#define BUCKET_NUM (2)

static bucket_liters_t bucket_size[BUCKET_NUM] = {0};
static bucket_liters_t bucket_state[BUCKET_NUM] = {0};

static uint32_t gcd(uint32_t a, uint32_t b)
{
    bool is_even_a = is_even(a);
    bool is_even_b = is_even(b);

    if (is_even_a && is_even_b)
    { // 都是偶数
        return 2 * gcd(a >> 1, b >> 1);
    }
    else if (is_even_a)
    { // a是偶数
        return gcd(a >> 1, b);
    }
    else if (is_even_b)
    { // b是偶数
        return gcd(a, b >> 1);
    }
    else
    { // 都是奇数
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

static bool is_possible(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume)
{
    return (goal_volume % gcd(bucket_1_size, bucket_2_size) == 0 &&
            (goal_volume <= bucket_1_size || goal_volume <= bucket_2_size));
}

static inline bool is_full(bucket_id_t bucket_id)
{
    return (bucket_state[bucket_id] == bucket_size[bucket_id]);
}

static inline bool is_empty(bucket_id_t bucket_id)
{
    return (bucket_state[bucket_id] == 0);
}

static inline bool is_reach(bucket_liters_t goal_volume)
{
    return (bucket_state[BUCKET_ID_1] == goal_volume || bucket_state[BUCKET_ID_2] == goal_volume);
}

static void empty(bucket_id_t bucket_id)
{
    bucket_state[bucket_id] = 0;

    printf("emptying bucket %d\n", bucket_id);
}

static void fill(bucket_id_t bucket_id)
{
    bucket_state[bucket_id] = bucket_size[bucket_id];

    printf("filling bucket %d\n", bucket_id);
}

static void pour(bucket_id_t from, bucket_id_t to)
{
    bucket_liters_t total = bucket_state[from] + bucket_state[to];
    bucket_state[to] = total > bucket_size[to] ? bucket_size[to] : total;
    bucket_state[from] = total > bucket_size[to] ? total - bucket_size[to] : 0;

    printf("pouring form bucket %d to %d\n", from, to);
}

static inline void print_bucket()
{
    printf("bucket state (%d, %d)\n", bucket_state[BUCKET_ID_1], bucket_state[BUCKET_ID_2]);
}

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket)
{
    bucket_result_t result = {0};

    if (!(result.possible = is_possible(bucket_1_size, bucket_2_size, goal_volume)))
    {
        return result;
    }

    if (bucket_1_size == goal_volume)
    {
        result.goal_bucket = BUCKET_ID_1;
        result.move_count = start_bucket == BUCKET_ID_1 ? 1 : 2;
        result.other_bucket_liters = start_bucket == BUCKET_ID_1 ? 0 : bucket_2_size;
    }
    else if (bucket_2_size == goal_volume)
    {
        result.goal_bucket = BUCKET_ID_2;
        result.move_count = start_bucket == BUCKET_ID_2 ? 1 : 2;
        result.other_bucket_liters = start_bucket == BUCKET_ID_2 ? 0 : bucket_1_size;
    }
    else
    {
        bucket_size[BUCKET_ID_1] = bucket_1_size;
        bucket_size[BUCKET_ID_2] = bucket_2_size;
        bucket_state[BUCKET_ID_1] = 0;
        bucket_state[BUCKET_ID_2] = 0;

        fill(start_bucket);
        result.move_count++;
        print_bucket();

        bucket_id_t non_start_bucket = (bucket_id_t)!start_bucket;

        while (!is_reach(goal_volume))
        {
            if (is_empty(start_bucket))
            {
                fill(start_bucket);
            }
            else if (!is_full(non_start_bucket))
            {
                pour(start_bucket, non_start_bucket);
            }
            else if (is_full(non_start_bucket))
            {
                empty(non_start_bucket);
            }

            print_bucket();

            result.move_count++;
        }

        result.goal_bucket = bucket_state[start_bucket] == goal_volume ? start_bucket : non_start_bucket;
        result.other_bucket_liters = bucket_state[!result.goal_bucket];
    }

    return result;
}