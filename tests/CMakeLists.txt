###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023
#

find_package(GTest MODULE REQUIRED)

set(GTEST_LIBS GTest::GTest GTest::Main)
set(DA_LIBS da::da)

add_executable(test_preprocessor test_preprocessor.cpp)
target_link_libraries(test_preprocessor PRIVATE ${GTEST_LIBS} ${DA_LIBS})

add_test(NAME test_preprocessor COMMAND test_preprocessor)
