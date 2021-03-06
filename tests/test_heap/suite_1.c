#include <unity.h>

#include "heap.h"

void test_norm(void)
{     
    struct vector vc;
    struct max_heap hp;
    int64_t tmp;

    TEST_ASSERT_EQUAL_UINT8(0, vector_create(&vc, 4));

    TEST_ASSERT_EQUAL_UINT8(0, vector_pushback(&vc, 2));
    TEST_ASSERT_EQUAL_UINT8(0, vector_pushback(&vc, 1));
    TEST_ASSERT_EQUAL_UINT8(0, vector_pushback(&vc, 3));
    TEST_ASSERT_EQUAL_UINT8(0, vector_pushback(&vc, 4));

    TEST_ASSERT_EQUAL_UINT8(0, heap_create_from_vector(&hp, &vc, 4));

    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 6));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 5));

    for(int32_t i = 0; i < 6; i++){
        TEST_ASSERT_EQUAL_UINT8(0, heap_top(&hp, &tmp));
        TEST_ASSERT_EQUAL_UINT8(0, heap_pop(&hp));
        TEST_ASSERT_EQUAL_INT64(6 - i, tmp);
        // 6 5 4 3 2 1
    }
    
    TEST_ASSERT_EQUAL_UINT8(0, heap_delete(&hp));
    TEST_ASSERT_EQUAL_UINT8(0, vector_delete(&vc));

    TEST_ASSERT_EQUAL_UINT8(0, heap_create(&hp));

    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 3));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 2));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 5));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 4));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 1));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 6));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 7));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 8));

    for(int32_t i = 0; i < 4; i++){
        TEST_ASSERT_EQUAL_UINT8(0, heap_top(&hp, &tmp));
        TEST_ASSERT_EQUAL_UINT8(0, heap_pop(&hp));
        TEST_ASSERT_EQUAL_INT64(8 - i, tmp);
        // 8 7 6 5
    }
    
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 4));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 9));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 2));
    TEST_ASSERT_EQUAL_UINT8(0, heap_insert(&hp, 10));

    for(int32_t i = 0; i < 8; i++){
        TEST_ASSERT_EQUAL_UINT8(0, heap_top(&hp, &tmp));
        TEST_ASSERT_EQUAL_UINT8(0, heap_pop(&hp));
        TEST_ASSERT_EQUAL_INT64(i < 2 ? (10 - i) : (i < 3 ? 4 : (i < 6 ? 7 - i : (8 - i))), tmp);
        // 10 9 4 4 3 2 2 1
    }

    TEST_ASSERT_EQUAL_UINT8(0, heap_delete(&hp));

}


int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_norm);
    return UNITY_END();
}
