#!/bin/bash
set -x
WD=$(pwd)

cmake --version
mkdir code_coverage_files
mkdir code_coverage_report

pip3 install --verbose -Ccmake.define.CMAKE_BUILD_TYPE=Debug \
                       -Ccmake.define.CMAKE_CXX_COMPILER=$CXX \
                       -Ccmake.define.CMAKE_CXX_FLAGS="$CFLAGS" \
                       -Ccmake.define.CMAKE_EXE_LINKER_FLAGS="$LFLAGS" \
                       -Ccmake.define.CMAKE_CXX_FLAGS_DEBUG="-O0" -e $WD

python3 -m pytest tests --cov=streampu --cov-report=lcov --cov-report=term

mv coverage.lcov code_coverage_files/streampu.info

lcov --capture --directory build/CMakeFiles/_ext.dir/src\
     --output-file code_coverage_files/_ext.info

rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
lcov --remove code_coverage_files/_ext.info "*/usr*" "lib/*" --output-file code_coverage_files/_ext_clean.info
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
lcov --add-tracefile code_coverage_files/_ext_clean.info -a code_coverage_files/streampu.info -o code_coverage_files/merged.info
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
lcov_cobertura code_coverage_files/merged.info --output code_coverage_report/streampu.xml
