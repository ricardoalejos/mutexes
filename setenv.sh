#!/usr/bin/env bash

export PROJECT_ROOT=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
export PROJECT_SOURCE=${PROJECT_ROOT}/source
export PROJECT_OUTPUT=${PROJECT_ROOT}/out
export PROJECT_BUILD=${PROJECT_OUTPUT}/build
export LD_LIBRARY_PATH=${PROJECT_OUTPUT}/lib:${LD_LIBRARY_PATH}
