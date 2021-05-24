
add_library(collections STATIC
    vector.c
    deque.c
    heap.c
)

target_include_directories(collections PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)