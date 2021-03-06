#include <unity.h>

#include "deque.h"

void test_norm(void)
{
    struct deque deq;
    struct deque deq_2;
    int64_t t = 0;
        
    TEST_ASSERT_EQUAL_UINT8(0, deque_create(&deq));
    TEST_ASSERT_EQUAL_UINT8(0, deque_create(&deq_2));
    
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq, 1));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq, 2));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq, 3));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq, 4));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq, 5));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pop_back(&deq));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pop_back(&deq));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq, 6));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq, 7));

    
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq_2, 8));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq_2, 9));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq_2, 10));
    TEST_ASSERT_EQUAL_UINT8(0, deque_pushback(&deq_2, 11));

    TEST_ASSERT_EQUAL_UINT8(0, deque_concat(&deq, &deq_2));

    for(int32_t i = 0; i < 9; i++){
        TEST_ASSERT_EQUAL_UINT8(0, deque_back(&deq, &t));
        TEST_ASSERT_EQUAL_INT64(i < 6 ? (11 - i) : 9 - i, t);
        TEST_ASSERT_EQUAL_UINT8(0, deque_pop_back(&deq));
    }

    TEST_ASSERT_EQUAL_UINT8(0, deque_delete(&deq));
    TEST_ASSERT_EQUAL_UINT8(0, deque_delete(&deq_2));
    
}


int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_norm);
    return UNITY_END();
}
