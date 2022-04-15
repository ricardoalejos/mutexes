#!/usr/bin/env bash

SCRIPT_DIR=$(dirname "${0}")
SCRIPT_ABS_DIR=$(readlink -f "${SCRIPT_DIR}")
ROOT_DIR="${SCRIPT_ABS_DIR}"/..
SOURCE_DIR=${ROOT_DIR}/source
OUTPUT_DIR=${ROOT_DIR}/out
BUILD_DIR=${OUTPUT_DIR}/build
LD_LIBRARY_PATH=${OUTPUT_DIR}/lib:${LD_LIBRARY_PATH}

${OUTPUT_DIR}/bin/test_smutex