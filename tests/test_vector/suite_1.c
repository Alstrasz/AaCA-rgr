#include <unity.h>

#include "vector.h"

void test_norm(void)
{
    struct vector vec;
    int64_t t = 0;
        
    TEST_ASSERT_EQUAL_UINT8(0, vector_create(&vec, 5));
    
    TEST_ASSERT_EQUAL_UINT8(0, vector_set(&vec, 0, 1));
    TEST_ASSERT_EQUAL_UINT8(0, vector_pushback(&vec, 2));
    TEST_ASSERT_EQUAL_UINT8(0, vector_pushback(&vec, 3));
    TEST_ASSERT_EQUAL_UINT8(0, vector_set(&vec, 3, 4));
    TEST_ASSERT_EQUAL_UINT8(0, vector_pushback(&vec, 5));

    TEST_ASSERT_EQUAL_UINT8(2, vector_set(&vec, 5, -1));
    TEST_ASSERT_EQUAL_UINT8(2, vector_pushback(&vec, -1));
     TEST_ASSERT_EQUAL_UINT8(2, vector_get(&vec, 5, &t));

    for(int32_t i = 0; i < 5; i++){
        TEST_ASSERT_EQUAL_UINT8(0, vector_get(&vec, i, &t));
        TEST_ASSERT_EQUAL_INT64(i + 1 , t);
    }
    
    TEST_ASSERT_EQUAL_UINT8(0, vector_resize(&vec, 8));

    for(int32_t i = 0; i < 8; i++){
        TEST_ASSERT_EQUAL_UINT8(0, vector_get(&vec, i, &t));
        TEST_ASSERT_EQUAL_INT64(i < 5 ? (i + 1) : 0, t);
    }

    TEST_ASSERT_EQUAL_INT8(0, vector_set(&vec, 5, 6));
    TEST_ASSERT_EQUAL_INT8(0, vector_pushback(&vec, 7));
    TEST_ASSERT_EQUAL_INT8(0, vector_set(&vec, 7, 8));
    
    TEST_ASSERT_EQUAL_UINT8(2, vector_pushback(&vec, -1));
    TEST_ASSERT_EQUAL_UINT8(2, vector_set(&vec, 8, -1));
    TEST_ASSERT_EQUAL_UINT8(2, vector_get(&vec, 8, &t));


    for(int32_t i = 0; i < 8; i++){
        TEST_ASSERT_EQUAL_UINT8(0, vector_get(&vec, i, &t));
        TEST_ASSERT_EQUAL_INT64(i + 1, t);
    }

    TEST_ASSERT_EQUAL_INT8(0, vector_delete(&vec));

}


int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_norm);
    return UNITY_END();
}
