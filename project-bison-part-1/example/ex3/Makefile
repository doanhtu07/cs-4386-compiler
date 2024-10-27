# Compiler settings
CC = gcc
BISON = bison
LEX = flex

# Output files
TARGET = ./build/ex3
BISON_OUTPUT = ./build/ex3
LEX_OUTPUT = ./build/ex3-lexer

# My main code files
BISON_FILE = ex3.y
LEX_FILE = ex3.l

LIB_PATH = /usr/local/opt/flex/lib

# Create build directory if it doesn't exist
$(shell mkdir -p build)

all: $(TARGET)

# Rule for compiling and linking
$(TARGET): $(BISON_OUTPUT).tab.c $(LEX_OUTPUT).yy.c
	$(CC) -o $(TARGET) $(BISON_OUTPUT).tab.c $(LEX_OUTPUT).yy.c -L$(LIB_PATH) -lfl

# Rule for generating the Bison parser
$(BISON_OUTPUT).tab.c $(BISON_OUTPUT).tab.h: $(BISON_FILE)
	$(BISON) -d -o $(BISON_OUTPUT).tab.c $(BISON_FILE)

# Rule for generating the Lex scanner
$(LEX_OUTPUT).yy.c: $(LEX_FILE)
	$(LEX) -o $(LEX_OUTPUT).yy.c $(LEX_FILE)

.PHONY: clean

# Clean up generated files
clean:
	rm -rf build

