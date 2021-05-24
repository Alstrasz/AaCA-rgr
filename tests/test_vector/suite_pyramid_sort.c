#include <unity.h>


#include "vector.h"

void test_norm(void)
{
    struct vector vec;
    int64_t t1, t2 = 0;

    vector_create(&vec, 9);

    vector_pushback(&vec, -3);
    vector_pushback(&vec, 3);
    vector_pushback(&vec, 2);
    vector_pushback(&vec, 0);
    vector_pushback(&vec, -2);
    vector_pushback(&vec, 1);
    vector_pushback(&vec, 4);
    vector_pushback(&vec, -1);
    vector_pushback(&vec, 5);

    //TEST_ASSERT_EQUAL_UINT8(0, 1);

    TEST_ASSERT_EQUAL_UINT8(0, vector_pyramid_sort(&vec, 9));

    for(int32_t i = 0; i < 8; i++)
    {
        vector_get(&vec, i, &t1);
        vector_get(&vec, i + 1, &t2);
        TEST_ASSERT_TRUE(t1 <= t2);
    }

    vector_delete(&vec);
}

void test_random(void)
{
    struct vector vec;
    int64_t t1, t2 = 0;
    uint64_t n = 2000;

    for(int32_t k = 0; k < 100; k++){
    
        vector_create(&vec, n);

        for(int32_t i = 0; i < n; i++)
        {
            vector_pushback(&vec, rand() % (n / 2));
        }

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, vector_pyramid_sort(&vec, n), "c");

        for(int32_t i = 0; i < n - 1; i++)
        {
            vector_get(&vec, i, &t1);
            vector_get(&vec, i + 1, &t2);
            TEST_ASSERT_TRUE_MESSAGE(t1 <= t2, "d");
        }

        vector_delete(&vec);

    }
}

void test_string(void)
{
    struct vector vec;
    int64_t t1, t2 = 0;

    vector_create(&vec, 9);
    vec.pointers = 1;

    char s1[] = "abc";
    char s2[] = "abcd";
    char s3[] = "abCd";
    char s4[] = "abcD";
    char s5[] = "aBcd";
    char s6[] = "Abcd";
    char s7[] = "Ad";
    char s8[] = "acd";
    char s9[] = "abc";

    vector_pushback(&vec, (int64_t) s1);
    vector_pushback(&vec, (int64_t) s2);
    vector_pushback(&vec, (int64_t) s3);
    vector_pushback(&vec, (int64_t) s4);
    vector_pushback(&vec, (int64_t) s5);
    vector_pushback(&vec, (int64_t) s6);
    vector_pushback(&vec, (int64_t) s7);
    vector_pushback(&vec, (int64_t) s8);
    vector_pushback(&vec, (int64_t) s9);
    

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, vector_pyramid_sort(&vec, 9), "e");

    for(int32_t i = 0; i < 8; i++)
    {
        vector_get(&vec, i, &t1);
        vector_get(&vec, i + 1, &t2);
        TEST_ASSERT_TRUE_MESSAGE(strcmp((char *) t1, (char *) t2) <= 0, "f");
    }

    vector_delete(&vec);

}

void test_random_string(void)
{
    struct vector vec;
    int64_t t1, t2 = 0;
    int32_t n = 200, len = 256, offset = 0;
    char * str;
    
    vector_create(&vec, n);
    
    for(int32_t i = 0; i < n; i++)
    {
        str = calloc(len + 1, sizeof(char));
        vector_pushback(&vec, (int64_t) str);
    }

    for(int32_t k = 0; k < 100; k++)
    {
        for(int32_t i = 0; i < n; i++)
        {
            vector_get(&vec, i, (int64_t *) str);
            offset = (rand() % 4) * 4;
            for(int32_t j = 0; j < len - offset; j++)
            {
                str[j] = (rand() % 255) + 1;
            }
            str[len - offset] = 0;
        }

        TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, vector_pyramid_sort(&vec, n), "k");

        for(int32_t i = 0; i < n - 1; i++)
        {
            vector_get(&vec, i, &t1);
            vector_get(&vec, i + 1, &t2);
            TEST_ASSERT_TRUE_MESSAGE(strcmp((char *) t1, (char *) t2) <= 0, "L");
        }
    }
}



int main(void)
{
    UNITY_BEGIN();
    
    RUN_TEST(test_norm);
    RUN_TEST(test_random);
    RUN_TEST(test_string);
    RUN_TEST(test_random_string);
    return UNITY_END();
}
