#include <unity.h>


void test_subnorm(void)
{
    TEST_ASSERT_EQUAL_INT32(3, 5);
    
}


int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_subnorm);
    return UNITY_END();
}
