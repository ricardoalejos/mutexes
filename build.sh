#!/usr/bin/env bash

SCRIPT_DIR=$(dirname "${0}")
ROOT_DIR=$(readlink -f "${SCRIPT_DIR}")
SOURCE_DIR=${ROOT_DIR}/source
OUTPUT_DIR=${ROOT_DIR}/out
BUILD_DIR=${OUTPUT_DIR}/build
LD_LIBRARY_PATH=${OUTPUT_DIR}/lib:${LD_LIBRARY_PATH}

cmake -S ${SOURCE_DIR} -B ${BUILD_DIR} -DCMAKE_INSTALL_PREFIX=${OUTPUT_DIR}
make -C ${BUILD_DIR} install
