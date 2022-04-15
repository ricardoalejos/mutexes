#!/usr/bin/env bash

SCRIPT_DIR=$(dirname "${0}")
SCRIPT_ABS_DIR=$(readlink -f "${SCRIPT_DIR}")
ROOT_DIR="${SCRIPT_ABS_DIR}"/..
OUTPUT_DIR=${ROOT_DIR}/out

rm -rf ${OUTPUT_DIR}
