add_executable(suite_1_heap
    suite_1.c
)

target_link_libraries(suite_1_heap
    collections
    Unity
)

add_test(suite_1_heap suite_1_heap)