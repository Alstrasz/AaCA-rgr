#ifndef M_DEQUE_H_DEF
#define M_DEQUE_H_DEF

#include "vector.h"

struct deque{
    struct vector *vec;
    uint32_t last_index;
    char vector_alloc;
};

char deque_create(struct deque* inp);

char deque_create_from_vector(struct deque* to, struct vector * from, uint32_t size);

char deque_pushback(struct deque* inp, int64_t elem);

char deque_back(struct deque* inp, int64_t *ret);

char deque_pop_back(struct deque* inp);

char deque_concat(struct deque* to, struct deque* from);

char deque_is_empty(struct deque* inp);

char deque_clear(struct deque* inp);

char deque_delete(struct deque* inp);

#endif
