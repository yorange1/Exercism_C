#include "nucleotide_count.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define BUFFER_SIZE (50)

char *count(const char *dna_strand)
{
    if (NULL == dna_strand)
    {
        return NULL;
    }

    size_t length = strlen(dna_strand);
    int count[4] = {0};

    char *ret = (char *)calloc(1, BUFFER_SIZE);
    if (NULL == ret)
    {
        return NULL;
    }

    for (size_t i = 0; i < length; i++)
    {
        switch (dna_strand[i])
        {
        case 'A':
            count[0]++;
            break;
        case 'C':
            count[1]++;
            break;
        case 'G':
            count[2]++;
            break;
        case 'T':
            count[3]++;
            break;
        default:
            return ret;
        }
    }

    sprintf(ret, "A:%d C:%d G:%d T:%d", count[0], count[1], count[2], count[3]);

    return ret;
}
