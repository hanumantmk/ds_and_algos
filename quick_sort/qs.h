#ifndef QS_HEADER
#define QS_HEADER

typedef int (* qs_comp_t)(void * a, void * b);

void qs_sort(void * data, int ele_size, int len, qs_comp_t comp);

#endif
