#!/usr/bin/env bash

SCRIPT_DIR=$(dirname "${0}")
ROOT_DIR=$(readlink -f "${SCRIPT_DIR}")
OUTPUT_DIR=${ROOT_DIR}/out

rm -rf ${OUTPUT_DIR}
