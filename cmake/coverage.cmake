###
# @file      coverage.cmake
# @brief     Provide custom target for code coverage
# @version   0.2
# @author    dragon-archer
#
# @copyright Copyright (c) 2023 dragon-archer
#

add_custom_target(code_coverage
	COMMAND ${CMAKE_COMMAND} -S${PROJECT_SOURCE_DIR} -B${PROJECT_BINARY_DIR}/code_coverage
		-DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage;-fprofile-arcs;-ftest-coverage;-DDA_ON_CODE_COVERAGE" -DDA_BuildTests=ON -DCMAKE_CXX_COMPILER=g++
	COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR}/code_coverage
	COMMAND lcov -d . -z
	COMMAND cd ${PROJECT_BINARY_DIR}/code_coverage && ${CMAKE_CTEST_COMMAND} --output-on-failure
	COMMAND lcov -d . -c -o cover.info --rc lcov_branch_coverage=1
	COMMAND lcov -e cover.info "*include/da/*" -o filtered.info --rc lcov_branch_coverage=1
	COMMENT "Compile and test with code coverage"
)
