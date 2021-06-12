#!/bin/bash

CC=nvcc
LDFLAGS=-lGLEW -lGLU -lGL -lglfw
DEBUG=-lineinfo

OBJ=src/App.o src/linear.o src/Chain.o src/openGLutils.o src/main.o
all: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(DEBUG) -o main

%.o: %.cpp
	$(CC) $(LDFLAGS) $(DEBUG) -c $< -o $@

%.o: %.cu
	$(CC) $(LDFLAGS) $(DEBUG) -c $< -o $@

clean:
	rm -v src/*.o
