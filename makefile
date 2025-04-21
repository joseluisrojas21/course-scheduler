# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O3

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
TEST_DIR = tests

# Source and object files
SRC_FILES = \
    $(SRC_DIR)/scheduler.c \
    $(SRC_DIR)/courses.c \
    $(SRC_DIR)/combination.c \
    $(SRC_DIR)/utils.c \
    $(SRC_DIR)/queue.c \
    $(SRC_DIR)/scheduleoptions.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable file name
EXEC = $(BIN_DIR)/scheduler

# Target to build the executable and then run tests
all: build $(EXEC)
	$(MAKE) -C $(TEST_DIR)

# Link the object files into the final executable
$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC)

# Compile source files into object files in the build directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test:
	$(MAKE) -C $(TEST_DIR)

# Clean up the build artifacts (object files and executable) and also clean the test directory
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)
	$(MAKE) -C $(TEST_DIR) clean

# Create necessary directories (bin and build)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build the object files and executable
build: $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean build test
