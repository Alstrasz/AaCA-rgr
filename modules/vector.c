#include "vector.h"
#include "heap.h"
#include "deque.h"
#include <stdio.h>

char vector_resize(struct vector* inp, uint32_t size)
{
    int64_t * ptr = (int64_t *)calloc(size, sizeof(int64_t));
    if(ptr == NULL)
    {
        return 1;

    }
    if(inp->data != NULL)
    {
        memcpy(ptr, inp->data, (inp->pos < size ? inp->pos : size) * sizeof(int64_t));
        free(inp->data);
    }
    
    inp->data = ptr;
    inp->pos = inp->pos < size ? inp->pos : size;
    inp->size = size;
    return 0;
}

char vector_create(struct vector* inp, uint32_t size)
{
    inp->size = 0;
    inp->pos = 0;
    inp->data = NULL;
    inp->pointers = 0;
    return vector_resize(inp, size);
}

char vector_pushback(struct vector* inp, int64_t elem)
{
    return vector_set(inp, inp->pos, elem);
}

char vector_get(struct vector* inp, uint32_t pos, int64_t * ret)
{
    if(pos >= inp->size)
    {
        return 2;
    }
    *ret = 1;
    *ret = inp->data[pos];
    return 0;
}

char vector_set(struct vector* inp, uint32_t pos, int64_t elem)
{
    if(pos >= inp->size)
    {
        return 2;
    }
    inp->data[pos] = elem;
    inp->pos = (pos + 1) > inp->pos ? (pos + 1) : inp->pos;
    return 0;
}

char vector_delete(struct vector* inp)
{
    free(inp->data);
    inp->size = 0;
    inp->pos = 0;
    return 0;
}

char vector_copy(struct vector* to, struct vector* from){
    char t;
    t = vector_delete(to);
    if(t > 0) return t;

    to->pos = from->pos;
    to->size = from->size;
    t = vector_resize(to, from->size);
    if(t > 0) return t;
    memcpy(to->data, from->data, to->size * sizeof(int64_t));
    return 0;
}

char vector_pyramid_sort(struct vector* inp, uint32_t size)
{
    struct max_heap mxh;
    char t = 0;
    int64_t max;

    t = heap_create_from_vector(&mxh, inp, size);
    if(t > 0) return t;

    for(uint32_t i = 0; i < size; i++)
    {
        t = heap_top(&mxh, &max);
        if(t > 0) return t;

        t = heap_pop(&mxh);
        if(t > 0) return t;

        t = vector_set(inp, size - 1 - i, max);
        if(t > 0) return t;
    }

    t = heap_delete(&mxh);
    if(t > 0) return t;
    
    return 0;
}

char vector_lexic_sort(struct vector* inp, uint32_t size, int32_t len)
{
    int64_t val;
    char t;
    
    if(!inp->pointers)
    {
        struct deque zero;
        struct deque one;
        struct deque ret;

        t = deque_create_from_vector(&ret, inp, size);
        if(t > 0) return t;
        t = deque_create(&zero);
        if(t > 0) return t;
        t = deque_create(&one);
        if(t > 0) return t;

        
        for(int32_t k = 0; k < len; k++)
        {
            for(uint32_t i = 0; i < size; i++)
            {
                t = vector_get(inp, i, &val);
                if(t > 0) return t;
                
                if((val & (1 << k)) >> k)
                {
                    t = deque_pushback(&one, val);
                    if(t > 0) return t;
                }else
                {
                    t = deque_pushback(&zero, val);
                    if(t > 0) return t;
                }
            }
            
            t = deque_clear(&ret);
            if(t > 0) return t;
            t = deque_concat(&ret, &zero);
            if(t > 0) return t;
            t = deque_concat(&ret, &one);
            if(t > 0) return t;
            t = deque_clear(&zero);
            if(t > 0) return t;
            t = deque_clear(&one);
            if(t > 0) return t;
        }

        t = deque_delete(&zero);
        if(t > 0) return t;
        t = deque_delete(&one);
        if(t > 0) return t;
        t = deque_delete(&ret);
        if(t > 0) return t;
    }
    else
    {
        int32_t symbol_count = 129;
        int32_t l;

        struct deque * alphabet = calloc(symbol_count, sizeof(struct deque));
        for(int32_t i = 0; i < symbol_count; i++)
        {
            t = deque_create(&alphabet[i]);
            if(t > 0) return t;
        }

        struct deque * str_by_len = calloc(len + 1, sizeof(struct deque));
        t = deque_create_from_vector(&str_by_len[0], inp, size);
        for(int32_t i = 1; i < len + 1; i++)
        {
            t = deque_create(&str_by_len[i]);
            if(t > 0) return t;
        }

        //printf("Deques created\n");
        
        deque_clear(&str_by_len[0]);
        
        for(uint32_t i = 0; i < size; i++)
        {
            t = vector_get(inp, i, &val);
            if(t > 0) return t;
            
            l = strlen((char *) val);

            t = deque_pushback(&str_by_len[l], val);
            if(t > 0) return t;
        }


        //printf("Deque initiated\n");
        
        for(int32_t k = len; k > 0; k--)
        {
            for(int32_t i = 0; i < str_by_len[k].last_index; i++)
            {
                t = vector_get(str_by_len[k].vec, i, &val);
                l++;
                if(t > 0) return t;

                t = deque_pushback(&alphabet[((char*) val)[k - 1] - 1], val);
                if(t > 0) return t;
            }

            //printf("%d\n", k);

            for(int32_t i = 0; i < symbol_count; i++)
            {
                t = deque_concat(&str_by_len[k - 1], &alphabet[i]);
                if(t > 0) return t;

                t = deque_clear(&alphabet[i]);
                if(t > 0) return t;
            }
        }

        //printf("Deque sorted\n");
        
        for(int32_t i = 0; i < len; i++)
        {
            t = deque_delete(&str_by_len[i]);
            if(t > 0) return t;
        }
        
        for(int32_t i = 0; i < symbol_count; i++)
        {
            t = deque_delete(&alphabet[i]);
            if(t > 0) return t;
        }

        //printf("Deques deleted\n");
    }
    
    return 0;
}
