SHELL = /usr/bin/env bash
CC = g++
CCFLAGS = -Wall -Wextra -Werror -std=c++14 -pedantic -g

.PHONY: compile-server run-server

TARGET = $(fn)

all: $(TARGET)

compile-specific:comp-$(TARGET)
	echo Compilation done

$(TARGET): comp-$(TARGET)
	./build/$(TARGET)

comp-$(TARGET):
	$(CC) $(CCFLAGS) -o ./build/$(TARGET) $(TARGET).cpp

compile-server:
	$(CC) $(CCFLAGS) -o server server.cpp

run-server: compile-server
	./server

compile-client:
	$(CC) $(CCFLAGS) -o client client.cpp

run-client: compile-client
	./client
