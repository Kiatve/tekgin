#!/usr/bin/env bash

# Parse input variables
for arg in "$@"; do
	eval "${arg%%=*}"=\'"${arg#*=}"\'
done

if [[ ${CLEAN,,} == "true" ]] || [[ ${CLEAN,,} == "yes" ]] || [[ ${CLEAN,,} == "on" ]]; then
	CLEAN=--clean-first
else
	CLEAN=""
fi

cmake -S . -G "Ninja Multi-Config" -B build $BUILD_ARGS

if [[ -z $CONFIG ]]; then
	cmake --build build $CLEAN
else
	for config in $(echo "$CONFIG" | tr ";" " "); do
		cmake --build build $CLEAN --config "$config" --parallel "${THREADS:-$(nproc)}"
	done
fi
