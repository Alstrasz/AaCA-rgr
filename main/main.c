#include "main.h"

void run_pyramidal_sort()
{
    FILE * file = fopen("input.txt", "r");
    uint32_t n = 0;
    int32_t l = 0;
    char * str = NULL;
    fscanf(file, "%u", &n);
        
    struct vector vec;

    vector_create(&vec, n);
    vec.pointers = 1;

    printf("Reading input\n");
        
    for(int32_t i = 0; i < n; i++)
    {
        fscanf(file, "%d", &l);
        if(l == 0)
        {
            printf("String size is 0. Break\n");
            exit(0);
        }
        str = calloc(l + 1, sizeof(char));
        fscanf(file, "%s", str);
        str[l] = 0;
        vector_pushback(&vec, (int64_t) str);
    }
    printf("Starting pyramidal sort\n");
    
    vector_pyramid_sort(&vec, n);


    for(int32_t i = 0; i < n; i++)
    {
        vector_get(&vec, i, (int64_t*) &str);
        printf("%s\n", str);
        free(str);
    }

    vector_delete(&vec);
    fclose(file);
}

void run_lexicographic_sort()
{
    FILE * file = fopen("input.txt", "r");
    uint32_t n = 0;
    int32_t l = 0, max_len = 0;
    char * str = NULL;
    fscanf(file, "%u", &n);
        
    struct vector vec;

    vector_create(&vec, n);
    vec.pointers = 1;

    printf("Reading input\n");
        
    for(int32_t i = 0; i < n; i++)
    {
        fscanf(file, "%d", &l);
        if(l == 0)
        {
            printf("String size is 0. Break\n");
            exit(0);
        }
        max_len = max_len > l ? max_len : l;
        str = calloc(l + 1, sizeof(char));
        fscanf(file, "%s", str);
        str[l] = 0;
        vector_pushback(&vec, (int64_t) str);
    }
    printf("Starting lexicographic sort\n");
    
    vector_lexic_sort(&vec, n, max_len);


    for(int32_t i = 0; i < n; i++)
    {
        vector_get(&vec, i, (int64_t*) &str);
        printf("%s\n", str);
        free(str);
    }

    vector_delete(&vec);
    fclose(file);
}

void benchmark()
{
    uint32_t n;
    int32_t len, max_offset, offset = 0;
    int64_t t1 = 0, t2 = 0;
    char * str = NULL;
    char * str2 = NULL;
    char c = 0;

    printf("Enter number of strings, maximun length and maximun offset\n");
    
    scanf("%u %d %d", &n, &len, &max_offset);

    struct vector vec1, vec2;

    vector_create(&vec1, n);
    vec1.pointers = 1;
    vector_create(&vec2, n);
    vec2.pointers = 1;
    
    for(int32_t i = 0; i < n; i++)
    {
        str = calloc(len + 1, sizeof(char));
        vector_pushback(&vec1, (int64_t) str);
        str2 = calloc(len + 1, sizeof(char));
        vector_pushback(&vec2, (int64_t) str2);
        if(str == NULL || str2 == NULL)
        {
            printf("Unable to allocate\n");
        }
    }
    
    printf("Memory allocated\n");

    for(int32_t i = 0; i < n; i++)
    {
        vector_get(&vec1, i, (int64_t *) str);
        vector_get(&vec2, i, (int64_t *) str2);
        if(max_offset != 0) offset = rand() % max_offset;
        for(int32_t j = 0; j < len - offset; j++)
        {
            c = (rand() % 127) + 1;
            str[j] = c;
            str2[j] = c;
        }
        str[len - offset] = 0;
        str2[len - offset] = 0;
    }

    printf("Strings have been generated\n");

    struct timeval stop1, start1, stop2, start2;

    gettimeofday(&start1, NULL);

    vector_pyramid_sort(&vec1, n);

    gettimeofday(&stop1, NULL);
    printf("Pyramidal sort is ended\n");
    c = 1;
    for(int32_t i = 0; i < n - 1; i++)
    {
        vector_get(&vec1, i, &t1);
        vector_get(&vec1, i + 1, &t2);
        c = c && (strcmp((char *) t1, (char *) t2) <= 0);
    }
    printf("Correctly sorted: %d. It took %lu us.\n\n", c, (stop1.tv_sec - start1.tv_sec) * 1000000 + stop1.tv_usec - start1.tv_usec);




    gettimeofday(&start2, NULL);
    
    vector_lexic_sort(&vec2, n, len);

    gettimeofday(&stop2, NULL);
    printf("Lexicographic sort is ended\n");
    c = 1;
    for(int32_t i = 0; i < n - 1; i++)
    {
        vector_get(&vec2, i, &t1);
        vector_get(&vec2, i + 1, &t2);
        c = c && (strcmp((char *) t1, (char *) t2) <= 0);
    }
    printf("Correctly sorted: %d. It took %lu us.\n\n", c, (stop2.tv_sec - start2.tv_sec) * 1000000 + stop2.tv_usec - start2.tv_usec);

    for(int32_t i = 0; i < n; i++)
    {
        vector_get(&vec1, i, (int64_t*) &str);
        free(str);
        vector_get(&vec2, i, (int64_t*) &str2);
        free(str2);
    }

    vector_delete(&vec1);
    vector_delete(&vec2);
}

int main( void )
{
    /*
    struct vector vc;
    struct max_heap hp;
    int64_t tmp;
    char t;

    if(0 != (t = vector_create(&vc, 4))) printf("a %d", t);

    if(0 != (t = vector_pushback(&vc, 2))) printf("b %d", t);
    if(0 != (t = vector_pushback(&vc, 1))) printf("c %d", t);
    if(0 != (t = vector_pushback(&vc, 3))) printf("d %d", t);
    if(0 != (t = vector_pushback(&vc, 4))) printf("e %d", t);

    if(0 != (t = heap_create_from_vector(&hp, &vc, 4))) printf("f %d", t);

    if(0 != (t = heap_insert(&hp, 6))) printf("L %d", t);
    if(0 != (t = heap_insert(&hp, 5))) printf("m %d", t);

    for(int32_t i = 0; i < 6; i++){
        if(0 != (t = heap_top(&hp, &tmp))) printf("g %d", t);
        if(0 != (t = heap_pop(&hp))) printf("h %d", t);
        printf("%ld ", tmp);
    }
    printf("\n");

    //if(0 != (t = vector_delete(&vc))) printf("i %d", t);
    if(0 != (t = heap_delete(&hp))) printf("j %d", t);

    if(0 != (t = heap_create(&hp))) printf("k %d", t);

    if(0 != (t = heap_insert(&hp, 3))) printf("i %d", t);
    if(0 != (t = heap_insert(&hp, 2))) printf("m %d", t);
    if(0 != (t = heap_insert(&hp, 5))) printf("n %d", t);
    if(0 != (t = heap_insert(&hp, 4))) printf("o %d", t);
    if(0 != (t = heap_insert(&hp, 1))) printf("p %d", t);
    if(0 != (t = heap_insert(&hp, 6))) printf("q %d", t);
    if(0 != (t = heap_insert(&hp, 7))) printf("r %d", t);
    if(0 != (t = heap_insert(&hp, 8))) printf("s %d", t);

    for(int32_t i = 0; i < 4; i++){
        if(0 != (t = heap_top(&hp, &tmp))) printf("t %d", t);
        if(0 != (t = heap_pop(&hp))) printf("u %d", t);
        printf("%ld ", tmp);
    }
    printf("\n");
    
    if(0 != (t = heap_insert(&hp, 4))) printf("p %d", t);
    if(0 != (t = heap_insert(&hp, 9))) printf("q %d", t);
    if(0 != (t = heap_insert(&hp, 2))) printf("r %d", t);
    if(0 != (t = heap_insert(&hp, 10))) printf("s %d", t);

        for(int32_t i = 0; i < 8; i++){
        if(0 != (t = heap_top(&hp, &tmp))) printf("t %d", t);
        if(0 != (t = heap_pop(&hp))) printf("u %d", t);
        printf("%ld ", tmp);
    }
    
    printf("\n");
    */

/*

    struct vector vec;
    int64_t t1, t2 = 0;

    vector_create(&vec, 9);

        vector_pushback(&vec, 4);
    vector_pushback(&vec, 3);
    vector_pushback(&vec, 2);
    vector_pushback(&vec, 0);
    vector_pushback(&vec, 3);
    vector_pushback(&vec, 1);
    vector_pushback(&vec, 4);
    vector_pushback(&vec, 1);
    vector_pushback(&vec, 5);

    vector_lexic_sort(&vec, 9, 64);

    for(int32_t i = 0; i < 9; i++)
    {
        vector_get(&vec, i, &t1);
        printf("%ld ", t1);
    }

    vector_delete(&vec);


*/
/*
    struct vector vec;
    int64_t t1;

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
    

    vector_lexic_sort(&vec, 9, 6);
    //vector_pyramid_sort(&vec, 9);

    for(int32_t i = 0; i < 9; i++)
    {
        vector_get(&vec, i, &t1);

        printf("%s\n", (char *)t1);
    }

    vector_delete(&vec);
*/
    uint32_t mode = 0;
    while(1){
        printf("\nChoose mode:\n0 for exit; 1 for pyramidal sort; 2 for lexicographic sort; 3 for benchmark\n");
        scanf("%u", &mode);
        if(mode == 0)
        {
            printf("Ending programm\n");
            return 0;
        }else if(mode == 1)
        {
            run_pyramidal_sort();
        }
        else if(mode == 2)
        {
            run_lexicographic_sort();
        }else if(mode == 3)
        {
            benchmark();
        }else
        {
            printf("Unknown mode\n");
        }
            
    }


    return 0;
}
