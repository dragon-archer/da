###
# @file      CMakeLists.txt
# @brief     CMake source file
# @version   0.1
# @author    dragon-archer
#
# @copyright Copyright (c) 2023 dragon-archer
#

cmake_minimum_required(VERSION 3.20) # For cxx_std_23
project(da VERSION 0.1 LANGUAGES CXX)

# Detect whether it is built as a subproject or a main project
set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(MAIN_PROJECT ON)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_23 DA_HasCxx23)

option(DA_BuildTests   "Build unit tests"                  ${MAIN_PROJECT})
option(DA_Coverage     "Enable code coverage target"       OFF)
option(DA_Install      "Install DA"                        ${MAIN_PROJECT})
option(DA_UseCxx23     "Enable C++23"                      ${DA_HasCxx23})
option(DA_UseStdFormat "Use std::format instead of fmtlib" OFF)

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

if(DA_UseCxx23)
	if(NOT DA_HasCxx23)
		message(FATAL_ERROR "DA is configured to use C++23 but the compiler does not support C++23")
	else()
		target_compile_features(${TARGET_NAME} INTERFACE cxx_std_23)
	endif()
else()
	list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_20 DA_HasCxx20)
	if(NOT DA_HasCxx20)
		message(FATAL_ERROR "DA should be compiled under at least C++20")
	endif()
	target_compile_features(${TARGET_NAME} INTERFACE cxx_std_20)
endif()

if(DA_UseStdFormat)
	target_compile_definitions(${TARGET_NAME} INTERFACE DA_USE_STD_FORMAT)
else()
	find_package(fmt REQUIRED)
	target_link_libraries(${TARGET_NAME} INTERFACE fmt::fmt-header-only)
endif()

target_include_directories(${TARGET_NAME} INTERFACE 
	$<BUILD_INTERFACE:${BUILD_INCLUDE_DIR}>
	$<INSTALL_INTERFACE:include>
)
# Enable new version of preprocessor for MSVC
target_compile_options(${TARGET_NAME} INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>)

# Tests
if(DA_BuildTests)
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
