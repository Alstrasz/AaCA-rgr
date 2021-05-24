add_executable(suite_1_vector
    suite_1.c
)


target_link_libraries(suite_1_vector
    collections
    Unity
)

add_test(suite_1_vector suite_1_vector)



add_executable(suite_pyramid_sort_vecotor
    suite_pyramid_sort.c
)


target_link_libraries(suite_pyramid_sort_vecotor
    collections
    Unity
)

add_test(suite_pyramid_sort_vecotor suite_pyramid_sort_vecotor)



add_executable(suite_lexic_sort_vecotor
    suite_lexic_sort.c
)

target_link_libraries(suite_lexic_sort_vecotor
    collections
    Unity
)

add_test(suite_lexic_sort_vecotor suite_lexic_sort_vecotor)

