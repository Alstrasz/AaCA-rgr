add_executable(suite_1_deque
    suite_1.c
)

target_link_libraries(suite_1_deque
    collections
    Unity
)

add_test(suite_1_deque suite_1_deque)