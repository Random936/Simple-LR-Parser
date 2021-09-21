CFiles=$(wildcard src/*.c)
CC=clang
CF=-Wall -g

install:
	$(CC) $(CF) $(CFiles) -o calc
