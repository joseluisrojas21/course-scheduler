CC = gcc
CFLAGS = -Wall -Wextra

# Source files
SRC_TEST = test_utils.c unity.c
SRC_SRC = ../src/utils.c

# Object files
OBJ_TEST = $(SRC_TEST:.c=.o)
OBJ_SRC = $(SRC_SRC:../src/%.c=../build/%.o)

# Executable
EXEC = test_utils

# Default target to compile everything and run tests
all: $(EXEC)
	@./$(EXEC)  # Run the test executable after compiling

# Link the object files into the final executable
$(EXEC): $(OBJ_TEST) $(OBJ_SRC)
	$(CC) $(OBJ_TEST) $(OBJ_SRC) -o $(EXEC)

# Compile test source files into object files (these stay in the test directory)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# General rule to compile any source file in ../src into ../build
../build/%.o: ../src/%.c | ../build
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the build directory exists
../build:
	mkdir -p ../build  # Fix: Create /build directory correctly

# Clean up build artifacts
clean:
	rm -f $(OBJ_TEST) $(OBJ_SRC) $(EXEC)

.PHONY: all clean
