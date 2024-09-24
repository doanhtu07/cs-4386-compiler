# Variables
CXX = g++
CXXFLAGS = -g -std=c++11 # -g is for debugging flag
TARGET = lexer
SRC = lexer.cpp
OBJ_DIR = build
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# Default rule to build the target
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the build directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean