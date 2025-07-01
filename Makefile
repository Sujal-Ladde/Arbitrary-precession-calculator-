# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g

# Include directory
INC_DIR = include

# Source directory
SRC_DIR = src

# Main source directory
MAIN_DIR = main

# Executable name
EXECUTABLE = a.out

# Output directory for object files
BIN_DIR = bin

# Create the bin directory if it doesn't exist
MKDIR_BIN = mkdir -p $(BIN_DIR)

# Source files
ADD_SRC = $(SRC_DIR)/ADD.c
SUB_SRC = $(SRC_DIR)/SUB.c
MUL_SRC = $(SRC_DIR)/MUL.c
DIV_SRC = $(SRC_DIR)/DIV.c
DLL_SRC = $(SRC_DIR)/DLL.c
MAIN_SRC = $(MAIN_DIR)/main.c

# Object files in the bin directory
ADD_OBJ = $(BIN_DIR)/ADD.o
SUB_OBJ = $(BIN_DIR)/SUB.o
DIV_OBJ = $(BIN_DIR)/DIV.o
MUL_OBJ = $(BIN_DIR)/MUL.o
DLL_OBJ = $(BIN_DIR)/DLL.o
MAIN_OBJ = $(BIN_DIR)/main.o

# Default target: compile and link
all: $(BIN_DIR) $(EXECUTABLE)

$(BIN_DIR):
	$(MKDIR_BIN)

# Compile object files and place them in the bin directory
$(BIN_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(ADD_OBJ): $(ADD_SRC) $(INC_DIR)/ADD.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(SUB_OBJ): $(SUB_SRC) $(INC_DIR)/SUB.h $(INC_DIR)/APC_DLL.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(MUL_OBJ): $(MUL_SRC) $(INC_DIR)/MUL.h $(INC_DIR)/APC_DLL.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(DIV_OBJ): $(DIV_SRC) $(INC_DIR)/DIV.h $(INC_DIR)/APC_DLL.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(DLL_OBJ): $(DLL_SRC) $(INC_DIR)/DLL.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(MAIN_OBJ): $(MAIN_SRC) $(INC_DIR)/APC_DLL.h  
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# Link object files from the bin directory to create the executable in the current directory
$(EXECUTABLE): $(ADD_OBJ) $(SUB_OBJ) $(MUL_OBJ) $(DIV_OBJ) $(DLL_OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Clean target: remove object files from the bin directory and the executable
clean:
	rm -rf $(BIN_DIR) $(EXECUTABLE)

.PHONY: all clean prepare-dirs