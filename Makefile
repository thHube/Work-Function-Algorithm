# ---------------------------------------------------------------------------- #
# -- Authors: Alberto Franco                                                -- #
# -- File:    Makefile                                                      -- #
# --                                                                        -- #
# -- Makefile per il progetto WORK                                          -- #
# ---------------------------------------------------------------------------- #
CC=g++
FLAG=-Wall -O3

all:
	$(CC) src/*.cpp $(FLAG) -o work
 
