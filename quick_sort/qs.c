#include "qs.h"

#include <alloca.h>
#include <string.h>
#include <stdio.h>


typedef struct qs_array {
    void * data;
    int ele_size;
    int len;
    qs_comp_t comp;
} qs_array_t;

void * qs__value(qs_array_t * info, int index)
{
    return (void *)((char *)info->data + (index * info->ele_size));
}

void qs__swap(qs_array_t * info, int a, int b)
{
    char * buf = alloca(info->ele_size);

    memcpy(buf, qs__value(info, a), info->ele_size);
    memcpy(qs__value(info, a), qs__value(info, b), info->ele_size);
    memcpy(qs__value(info, b), buf, info->ele_size);
}

int qs__partition(qs_array_t * info, int left, int right, int pivot)
{
    char * buf = alloca(info->ele_size);

    memcpy(buf, qs__value(info, pivot), info->ele_size);

    qs__swap(info, pivot, right);

    int stored = left;

    for (int i = left; i < right; i++) {
        if (info->comp(qs__value(info, i), buf) < 0) {
            qs__swap(info, i, stored);
            stored++;
        }
    }

    qs__swap(info, stored, right);

    return stored;
}

void qs__sort(qs_array_t * info, int left, int right)
{
    if (left < right) {
        int pivot = (right + left) / 2;

        int new_pivot = qs__partition(info, left, right, pivot);
        qs__sort(info, left, new_pivot - 1);
        qs__sort(info, new_pivot + 1, right);
    }
}

void qs_sort(void * data, int ele_size, int len, qs_comp_t comp)
{
    qs_array_t info = {
        .data     = data,
        .ele_size = ele_size,
        .len      = len,
        .comp     = comp,
    };

    qs__sort(&info, 0, len - 1);
}
