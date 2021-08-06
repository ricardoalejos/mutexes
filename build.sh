#!/usr/bin/env bash

export PROJECT_ROOT=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
export PROJECT_SOURCE=${PROJECT_ROOT}/source
export PROJECT_OUTPUT=${PROJECT_ROOT}/out
export PROJECT_BUILD=${PROJECT_OUTPUT}/build

cmake -S ${PROJECT_SOURCE} -B ${PROJECT_BUILD} -DCMAKE_INSTALL_PREFIX=${PROJECT_OUTPUT}
make -C ${PROJECT_BUILD} install
