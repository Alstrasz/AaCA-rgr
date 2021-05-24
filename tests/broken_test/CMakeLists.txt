add_executable(meant_to_fail
    meant_to_fail.c
)
add_executable(meant_to_be_fine
    meant_to_be_fine.c
)

target_link_libraries(meant_to_fail
    Unity
)
target_link_libraries(meant_to_be_fine
    Unity
)

add_test(meant_to_fail meant_to_fail)
add_test(meant_to_be_fine meant_to_be_fine)