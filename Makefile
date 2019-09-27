#Compiler
CC := g++

#Target Binary
TARGET := Xinex

#Source, include, and target directories
SRC_DIR := src
INCLUDE_DIR := include
TARGET_DIR := bin

#Linker options
PSAPI := psapi


#Flags
CFLAGS := -Wall -g
STD := -std=c++17

#test -d $(TARGET_DIR) || mkdir $(TARGET_DIR)
xinexmake:
	$(CC) $(SRC_DIR)/*.cpp -o $(TARGET) $(STD) $(CFLAGS) -I$(INCLUDE_DIR) -l$(PSAPI)
