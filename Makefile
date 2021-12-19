SHELL = /usr/bin/env bash
CC = g++
CCFLAGS = -Wall -Wextra -Werror -std=c++14 -pedantic -g

.PHONY: compile-server run-server

compile-server:
	$(CC) $(CCFLAGS) -o server server.cpp

run-server: compile-server
	./server

compile-client:
	$(CC) $(CCFLAGS) -o client client.cpp

run-client: compile-client
	./client
