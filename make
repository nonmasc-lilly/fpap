#!/usr/bin/env bash

CFLAGS="-std=c90 -Wpedantic"
DEBUG=false
TEST=false
while getopts "dt" OPT; do
	case $OPT in
	d) DEBUG=true;;
	t) TEST=true
	esac
done

if [[ ! -d build/ ]]; then
	mkdir -p build
fi

if [[ $DEBUG = true ]]; then
	CFLAGS="$CFLAGS -g"
fi

cc $CFLAGS -c -o build/fpap.o src/fpap.c -DWIN_GLFW || exit 1

if [[ $TEST = true ]]; then
	cc $CFLAGS -lGL -lglfw -o build/test src/test.c build/fpap.o || exit 1
	if [[ $DEBUG = true ]]; then
		gdb build/test
	else
		build/test
	fi
fi
