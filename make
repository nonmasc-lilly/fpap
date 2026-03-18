#!/usr/bin/env bash

TARGET="fpap"
CFLAGS="-std=c90 -Wpedantic"
DEBUG=false
SPEC=false
TEST=false
LIB=false
INSTALL=false
ARCHIVE=false
while getopts "dilst" OPT; do
	case $OPT in
	d) DEBUG=true;;
	i) INSTALL=true;;
	l) LIB=true;;
	s) SPEC=true;;
	t) TEST=true;;
	esac
done

if [[ ! -d build/ ]]; then
	mkdir -p build
fi

if [[ $SPEC = true ]]; then
	pdftex -jobname=fpap-spec -output-directory=build docs/main.tex\
	|| exit 1
fi

if [[ $DEBUG = true ]]; then
	CFLAGS="$CFLAGS -g"
	if [[ $INSTALL = true ]]; then
		TARGET="D$TARGET"
	fi
fi
if [[ $LIB = true ]]; then
	ITARGET="/usr/lib/lib$TARGET.so"
	TARGET="build/$TARGET.so"
	CFLAGS="$CFLAGS -shared -fPIC"
else
	ARCHIVE=true
	ITARGET="/usr/lib/lib$TARGET.a"
	TARGET="build/$TARGET.o"
	CFLAGS="$CFLAGS -c"
fi


cc $CFLAGS -o $TARGET src/fpap.c -DWIN_GLFW || exit 1

if [[ $TEST = true ]]; then
	cc -std=c90 -Wpedantic -lGL -lglfw -o build/test src/test.c\
		$TARGET || exit 1
	if [[ $DEBUG = true ]]; then
		gdb build/test
	else
		build/test
	fi
fi

if [[ $INSTALL = true ]]; then
	if [[ $ARCHIVE = true ]]; then
		ar --output build libfpap.a $TARGET
		TARGET=build/libfpap.a
	fi
	cp $TARGET $ITARGET
	cp src/fpap.h /usr/include/fpap.h
fi
