# Compiler
CC := g++

# Target bin
TARGET := guan

# directories
INCLUDE_DIR := include
SRC_DIR := src

# Flags
FLAGS := -std=c++17 -g -Wall

# Links
FS := stdc++fs

# Make
guanmake:
	$(CC) $(SRC_DIR)/*.cpp -o $(TARGET) $(FLAGS) -I$(INCLUDE_DIR) -l$(FS)
