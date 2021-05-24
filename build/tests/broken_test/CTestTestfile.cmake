# CMake generated Testfile for 
# Source directory: /home/alstrasz/Documents/c-karlov-rgr-proj (git_test)/tests/broken_test
# Build directory: /home/alstrasz/Documents/c-karlov-rgr-proj (git_test)/build/tests/broken_test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(meant_to_fail "meant_to_fail")
set_tests_properties(meant_to_fail PROPERTIES  _BACKTRACE_TRIPLES "/home/alstrasz/Documents/c-karlov-rgr-proj (git_test)/tests/broken_test/CMakeLists.txt;15;add_test;/home/alstrasz/Documents/c-karlov-rgr-proj (git_test)/tests/broken_test/CMakeLists.txt;0;")
add_test(meant_to_be_fine "meant_to_be_fine")
set_tests_properties(meant_to_be_fine PROPERTIES  _BACKTRACE_TRIPLES "/home/alstrasz/Documents/c-karlov-rgr-proj (git_test)/tests/broken_test/CMakeLists.txt;16;add_test;/home/alstrasz/Documents/c-karlov-rgr-proj (git_test)/tests/broken_test/CMakeLists.txt;0;")
