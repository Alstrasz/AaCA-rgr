#include "heap.h"


char heap_create(struct max_heap *inp)
{
    inp->last_index = 0;
    inp->vector_alloc = 1;
    inp->vec = (struct vector *)calloc(1, sizeof(struct vector));
    return vector_create(inp->vec, 4);
}

char heap_create_from_vector(struct max_heap *inp, struct vector *from, uint32_t size)
{
    inp->vector_alloc = 0;
    char t;
    //  t = vector_copy(inp->vec, from);
    //  if(t > 0) return t;
    inp->vec = from;
    inp->last_index = size;
    for(uint32_t i = 0; i < inp->last_index; i++)
    {
        t = heap_fix(inp, inp->last_index - 1 - i);
        if(t > 0) return t;
    }
    return 0;
}

char heap_top(struct max_heap *inp, int64_t *ret)
{
    return vector_get(inp->vec, 0, ret);
}

char heap_pop(struct max_heap *inp)
{
    char t;
    int64_t val;
    t = vector_get(inp->vec, inp->last_index - 1, &val);
    if(t > 0) return t;
    t = vector_set(inp->vec, 0, val);
    if(t > 0) return t;
    t = heap_fix(inp, 0);
    if(t > 0) return t;

    inp->last_index--;
    
    return 0;
}

char heap_insert(struct max_heap *inp, int64_t elem){
    char t;

    if(inp->last_index >= inp->vec->size)
    {
        t = vector_resize(inp->vec, inp->last_index * 2);
        if(t > 0) return t;
    }
    
    t = vector_set(inp->vec, inp->last_index, INT64_MIN);
    if(t > 0) return t;
    
    t = heap_change_val(inp, inp->last_index, elem);
    if(t > 0) return t;

    inp->last_index++;
    
    return 0;
}

char heap_fix(struct max_heap *inp, uint32_t index)
{
    char t;
    uint32_t left = (index) * 2 + 1;
    uint32_t right = (index) * 2 + 2;
    uint32_t largest = index;
    char greater = 0;
    
    int64_t curr_val = -1,left_val = -1, right_val = -1;
    t = vector_get(inp->vec, index, &curr_val);
    if(t > 0) return t;
    
    if(left < inp->last_index)
    {
            t = vector_get(inp->vec, left, &left_val);
            if(t > 0) return t;
            greater = inp->vec->pointers > 0 ? (strcmp((char*) left_val, (char*) curr_val) > 0) : (left_val > curr_val);
            if(greater)
            {
                largest = left;
                curr_val = left_val;
            }
    }
    if(right < inp->last_index)
    {
        t = vector_get(inp->vec, right, &right_val);
        if(t > 0) return t;
        greater = inp->vec->pointers > 0 ? (strcmp((char*) right_val, (char*) curr_val) > 0) : (right_val > curr_val);
        if(greater)
        {
            largest = right;
            curr_val = right_val;
        }
    }
    if(largest != index){
        t = vector_get(inp->vec, index, &curr_val);
        if(t > 0) return t;
        t = vector_get(inp->vec, largest, &left_val);
        if(t > 0) return t;
        t = vector_set(inp->vec, largest, curr_val);
        if(t > 0) return t;
        t = vector_set(inp->vec, index, left_val);
        if(t > 0) return t;
        heap_fix(inp, largest);
    }
    
    return 0;
}
/*
              0
     1               2
  3     4        5       6
7   8  9  10    11  12  13  14
*/
char heap_delete(struct max_heap *inp)
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

char heap_change_val(struct max_heap *inp, uint32_t pos, int64_t val)
{
    char t = 0;
    int64_t old_val;
    char greater;
    t = vector_get(inp->vec, pos, &old_val);
    if (t > 0) return t;
    
    greater = inp->vec->pointers > 0 ? (strcmp((char*) val, (char*) old_val) > 0) : (val > old_val);
    if (greater == 0) return 3;

    t = vector_set(inp->vec, pos, val);
    if (t > 0) return t;

    if(pos == 0) return 0;
    
    uint32_t parent = (pos - 1) / 2;
    t = vector_get(inp->vec, parent, &old_val);
    if (t > 0) return t;

    greater = inp->vec->pointers > 0 ? (strcmp((char*) val, (char*) old_val) > 0) : (val > old_val);
    while(greater){
        t = vector_set(inp->vec, pos, old_val);
        if (t > 0) return t;

        t = vector_set(inp->vec, parent, val);
        if (t > 0) return t;

        pos = parent;

        if(pos == 0) break;
        
        parent = (pos - 1) / 2;
        t = vector_get(inp->vec, parent, &old_val);
        if (t > 0) return t;
        greater = inp->vec->pointers > 0 ? (strcmp((char*) val, (char*) old_val) > 0) : (val > old_val);
    }
    
    return 0;
}
