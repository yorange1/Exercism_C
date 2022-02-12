#include "minesweeper.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void update(char **annotation, size_t row, size_t col, size_t rows, size_t cols)
{
    size_t row_begin = row > 0 ? row - 1 : 0;
    size_t row_end = row + 1 < rows ? row + 1 : row;
    size_t col_begin = col > 0 ? col - 1 : 0;
    size_t col_end = col + 1 < cols ? col + 1 : col;

    for (size_t i = row_begin; i <= row_end; i++)
    {
        for (size_t j = col_begin; j <= col_end; j++)
        {
            switch (annotation[i][j])
            {
            case '*':
                break;
            case ' ':
                annotation[i][j] = '1';
                break;
            default:
                annotation[i][j]++;
                break;
            }
        }
    }
}

char **annotate(const char **minefield, const size_t rows)
{
    if (0 == rows)
    {
        return NULL;
    }

    size_t cols = strlen(minefield[0]) + 1;
    char **annotation = (char **)malloc(rows * sizeof(char *));
    assert(annotation != NULL);

    for (size_t row = 0; row < rows; row++)
    {
        annotation[row] = (char *)calloc(1, cols);
        assert(annotation[row] != NULL);
        strcpy(annotation[row], minefield[row]);
    }

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t col = 0; col < cols - 1; col++)
        {
            if ('*' == annotation[row][col])
            {
                update(annotation, row, col, rows, cols - 1);
            }
        }
    }

    return annotation;
}

void free_annotation(char **annotation)
{
    assert(annotation != NULL);

    free(annotation);
}
