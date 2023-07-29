###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023 dragon-archer
#

cmake_minimum_required(VERSION 3.16)
project(da VERSION 0.1 LANGUAGES CXX)

# Detect whether it is built as a subproject or a main project
set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(MAIN_PROJECT ON)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

option(DA_BuildTests "Build unit tests" ${MAIN_PROJECT})
option(DA_Install    "Install ${PROJECT_NAME}" ${MAIN_PROJECT})
option(DA_Coverage   "Enable code coverage target" OFF)

if(USE_CCACHE)
	find_program(CCACHE_FOUND ccache)
	if(CCACHE_FOUND)
		set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
		set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
	endif()
endif()

if(DA_Coverage)
	include(coverage)
endif()

include(GNUInstallDirs)

set(TARGET_NAME         ${PROJECT_NAME})
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR})
set(INSTALL_CMAKE_DIR   ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
set(BUILD_INCLUDE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${TARGET_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_20 DA_HAS_CXX20)
if(NOT DA_HAS_CXX20)
	message(FATAL_ERROR "DA should be compiled under at least C++20")
endif()
if(DA_USE_CXX23)
	list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_23 DA_HAS_CXX23)
	if(NOT DA_HAS_CXX23)
		message(STATUS "No suitable C++23 support, use C++20 instead")
		target_compile_features(${TARGET_NAME} INTERFACE cxx_std_20)
	else()
		target_compile_features(${TARGET_NAME} INTERFACE cxx_std_23)
	endif()
else()
	target_compile_features(${TARGET_NAME} INTERFACE cxx_std_20)
endif()

target_include_directories(${TARGET_NAME} INTERFACE 
	$<BUILD_INTERFACE:${BUILD_INCLUDE_DIR}>
	$<INSTALL_INTERFACE:include>
)
# Enable new version of preprocessor for MSVC
target_compile_options(${TARGET_NAME} INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>)

# Tests
if(DA_BuildTests)
	set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1) # Forbid CTest to add targets
	include(CTest)
	enable_testing()
	add_subdirectory(tests)
endif()

# Configure CMake Package
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
	ARCH_INDEPENDENT
)

configure_package_config_file(
	${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
	INSTALL_DESTINATION ${INSTALL_CMAKE_DIR}
)

# Install
if(DA_Install)
	install(
		DIRECTORY ${BUILD_INCLUDE_DIR}
		DESTINATION ${INSTALL_INCLUDE_DIR}
	)

	install(
		TARGETS ${TARGET_NAME}
		EXPORT ${PROJECT_NAME}-targets
	)

	install(
		EXPORT      ${PROJECT_NAME}-targets
		NAMESPACE   "${PROJECT_NAME}::"
		DESTINATION ${INSTALL_CMAKE_DIR}
	)

	install(
		FILES
			${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
			${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
		DESTINATION
			${INSTALL_CMAKE_DIR}
	)
endif()
