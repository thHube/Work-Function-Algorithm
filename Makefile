# ---------------------------------------------------------------------------- #
# -- Authors: Alberto Franco                                                -- #
# -- File:    Makefile                                                      -- #
# -- Brief:   Makefile for WORK project                                     -- #
# ---------------------------------------------------------------------------- #
CC=g++
# CC=i586-mingw32msvc-c++ # -- TO compile from linux to windows ----------------
FLAG=-Wall -O3

TARGET="bin/work"

all:
	mkdir bin
	$(CC) src/*.cpp $(FLAG) -o $(TARGET)
 
clean:
	rm -r bin

