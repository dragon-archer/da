###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023
#

set(GTEST_LIBS gtest gtest_main)

add_executable(test_preprocessor test_preprocessor.cpp)
target_link_libraries(test_preprocessor ${GTEST_LIBS})

add_test(NAME test_preprocessor COMMAND test_preprocessor)
