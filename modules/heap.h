#ifndef M_HEAP_H_DEF
#define M_HEAP_H_DEF

#include "vector.h"

struct max_heap{
    struct vector *vec;
    uint32_t last_index;
    char vector_alloc;
};

char heap_create(struct max_heap *inp);

char heap_create_from_vector(struct max_heap *inp, struct vector *from, uint32_t size);

char heap_top(struct max_heap *inp, int64_t *ret);

char heap_pop(struct max_heap *inp);

char heap_insert(struct max_heap *inp, int64_t elem);

char heap_fix(struct max_heap *inp, uint32_t index);

char heap_delete(struct max_heap *inp);

char heap_change_val(struct max_heap *inp, uint32_t pos, int64_t val);

#endif
