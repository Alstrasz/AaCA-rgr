#include "deque.h"

char deque_create(struct deque* inp)
{
    inp->last_index = 0;
    inp->vector_alloc = 1;
    inp->vec = (struct vector *)calloc(1, sizeof(struct vector));
    if(inp->vec == 0) return 1; 
    return vector_create(inp->vec, 4);
}


char deque_create_from_vector(struct deque* to, struct vector * from, uint32_t size)
{
    to->vector_alloc = 0;
    to->vec = from;
    to->last_index = size;
    return 0;
}

char deque_pushback(struct deque* inp, int64_t elem)
{
    char t = 0;
    if(inp->last_index >= inp->vec->size)
    {
        if((t = vector_resize(inp->vec, 2 * inp->last_index)) > 0)
        {
            return t;
        }
    }
    t = vector_set(inp->vec, inp->last_index, elem);
    if (t > 0) return t;
    inp->last_index++;
    return 0;
}

char deque_back(struct deque* inp, int64_t *ret)
{
    if(inp->last_index <= 0)
    {
        return 2;
    }
    return vector_get(inp->vec, inp->last_index - 1, ret);
}

char deque_pop_back(struct deque* inp){
    if(inp->last_index <= 0)
    {
        return 2;
    }
    inp->last_index--;
    return 0;
}

char deque_delete(struct deque* inp)
{
    char t = 0;
    inp->last_index = 0;
    if(inp->vector_alloc){
        t = vector_delete(inp->vec);
        free(inp->vec);
    }else
    {
        inp->vec = NULL;
    }
    return t;   
}

char deque_clear(struct deque* inp)
{
    inp->last_index = 0;
    return 0;
}

char deque_concat(struct deque* to, struct deque* from){
    int64_t temp;
    char ret = 0;
    for(uint64_t i = 0; i < from->last_index; i++)
    {
        ret = vector_get(from->vec, i, &temp);
        if(ret > 0) return ret;
        ret = deque_pushback(to, temp);
        if(ret > 0) return ret;
    }
    return 0;
}

char deque_is_empty(struct deque* inp)
{
    return inp->last_index == 0;
}
