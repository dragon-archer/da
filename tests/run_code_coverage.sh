#!/bin/sh
cd $(dirname $0) && \
mkdir -p ../out/coverage && \
cd ../out/coverage && 
cmake -S../.. -B. -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage -fprofile-arcs -ftest-coverage -DDA_ON_CODE_COVERAGE" -DDA_BuildTests=ON -DUSE_CCACHE=True -DCMAKE_CXX_COMPILER=g++ && \
cmake --build . && 
lcov -d . -z && \
ctest --output-on-failure && \
lcov -d . -c -o cover.info --rc lcov_branch_coverage=1 && \
lcov -e cover.info "*include/da/*" -o filtered.info --rc lcov_branch_coverage=1 && \
genhtml -t DA --legend --demangle-cpp -o html -s --branch-coverage filtered.info
