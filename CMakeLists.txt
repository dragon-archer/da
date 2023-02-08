###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023
#

cmake_minimum_required(VERSION 3.16)
project(libda VERSION 0.1 LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	set_property(DIRECTORY PROPERTY COMPILE_OPTIONS "/Zc:preprocessor") # For __VA_OPT__ support
endif()

add_subdirectory(test)
