# ---------------------------------------------------------------------------- #
# -- Authors: Alberto Franco                                                -- #
# -- File:    Makefile                                                      -- #
# -- Brief:   Makefile for WORK project                                     -- #
# ---------------------------------------------------------------------------- #
CC=g++
FLAG=-Wall -O3

TARGET="bin/work"

all:
	mkdir bin
	$(CC) src/*.cpp $(FLAG) -o $(TARGET)
 
clean:
	rm $(TARGET)
	rm -r bin

