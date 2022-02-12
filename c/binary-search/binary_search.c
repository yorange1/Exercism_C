#include "binary_search.h"

int *binary_search(int value, const int *arr, size_t length)
{
    int left = 0;
    int right = length - 1;
    

    int *result = NULL;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] == value)
        {
            result = (int *)&arr[mid];
            break;
        }
        else if (arr[mid] > value)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return result;
}
