#ifndef M_VECTOR_H_DEF
#define M_VECTOR_H_DEF
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct vector{
    int64_t * data;
    uint32_t size;
    uint32_t pos;
    char pointers;
};

char vector_resize(struct vector* inp, uint32_t size);

char vector_create(struct vector* inp, uint32_t size);

char vector_pushback(struct vector* inp, int64_t elem);

char vector_get(struct vector* inp, uint32_t pos, int64_t * ret);

char vector_set(struct vector* inp, uint32_t pos, int64_t elem);

char vector_copy(struct vector* to, struct vector* from);

char vector_delete(struct vector* inp);

char vector_pyramid_sort(struct vector* inp, uint32_t size);

char vector_lexic_sort(struct vector* inp, uint32_t size, int32_t len);

#endif
