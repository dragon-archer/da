###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023 dragon-archer
#

add_library(test_main OBJECT unit.cpp)
target_compile_definitions(test_main PUBLIC
	DOCTEST_CONFIG_SUPER_FAST_ASSERTS
	DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
)
target_link_libraries(test_main PUBLIC ${TARGET_NAME})
target_include_directories(test_main PUBLIC thirdparty)

file(GLOB UNIT_SRC unit-*.cpp)
message(STATUS "Find unit test files: ${UNIT_SRC}")
foreach(unit_src ${UNIT_SRC})
	message(STATUS "Add unit test for ${unit_src}")
	string(REGEX MATCH "unit-[^.]+" unit_name ${unit_src})
	message(STATUS "Unit test name: ${unit_name}")
	add_executable(${unit_name} ${unit_src})
	target_link_libraries(${unit_name} PRIVATE test_main)
	add_test(NAME ${unit_name} COMMAND ${unit_name})
endforeach()
