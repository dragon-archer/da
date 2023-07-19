###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023 dragon-archer
#

set(SRC
	config.hpp
	main.cpp
	object.hpp
)

set(PCH pch.hpp)

add_executable(dascript ${SRC})
target_precompile_headers(dascript PRIVATE ${PCH})
target_link_libraries(dascript PRIVATE da)
