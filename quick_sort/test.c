#include "qs.h"

#include <stdio.h>
#include <string.h>

int comp(void * a, void * b)
{
    return *((int *)a) - *((int *)b);
}

int str_comp(void * a, void * b)
{
    printf("comparing %s and %s\n", *(char **)a, *(char **)b);
    return strcmp(*(char **)a, *(char **)b);
}

int main(int argc, char ** argv)
{

    char * foo[] = { "foo", "bar", "baz", "zzz", "aaa" };
    int array[] = {5, 4, 3, 2, 1};

    qs_sort(array, sizeof(int), 5, &comp);
    qs_sort(foo, sizeof(char *), 5, &str_comp);

    for (int i = 0; i < 5; i++) {
        printf("%d, ", array[i]);
    }
    printf("\n");

    for (int i = 0; i < 5; i++) {
        printf("%s, ", foo[i]);
    }
    printf("\n");
}
