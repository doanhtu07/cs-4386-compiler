# Define variables
LEX = flex
CC = gcc
LEX_FILE = my-lexer.l
C_FILE = lex.yy.c
OUTPUT = lexer

# Targets

all: $(OUTPUT)

$(OUTPUT): $(C_FILE)
	$(CC) $(C_FILE) -o $(OUTPUT)

$(C_FILE): $(LEX_FILE)
	$(LEX) $(LEX_FILE)

clean:
	rm -f $(C_FILE) $(OUTPUT)