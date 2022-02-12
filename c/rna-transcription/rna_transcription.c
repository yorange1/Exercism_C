#include "rna_transcription.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// G -> C
// C -> G
// T -> A
// A -> U

char *to_rna(const char *dna)
{
    if (NULL == dna)
    {
        return NULL;
    }

    size_t length = strlen(dna);
    char *ret_str = (char *)calloc(1, length + 1);

    for (size_t i = 0; i < length; i++)
    {
        switch (dna[i])
        {
        case 'G':
            ret_str[i] = 'C';
            break;
        case 'C':
            ret_str[i] = 'G';
            break;
        case 'T':
            ret_str[i] = 'A';
            break;
        case 'A':
            ret_str[i] = 'U';
            break;
        default:
            return NULL;
        }
    }

    return ret_str;
}
