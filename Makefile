# Compiler, flags, and libraries
CC = g++
CFLAGS = -std=c++11 -Wall -I./include -I./test
LIBS_TEST = -lgtest -lpthread

# Files
SRC = $(wildcard ./src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = matrix

# Main file
MAIN = $(wildcard main.cpp)
MAIN_OBJ = $(MAIN:.cpp=.o)
MAIN_EXE = $(MAIN:.cpp=)

# Test files
TEST = $(wildcard ./test/*.cpp)
TEST_OBJ = $(TEST:.cpp=.o)
TEST_EXE = $(TEST:.cpp=)

all : test

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

test : $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ $(LIBS_TEST) -o $(TEST_EXE)
	./$(TEST_EXE)

main : $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@
	./$@

clean_obj :
	rm -rf $(TEST_OBJ) $(OBJ) $(MAIN_OBJ)
	clear

clean_exe :
	rm -rf $(TEST_EXE) $(MAIN_EXE) $(EXE)
	clear

clean : clean_obj clean_exe

docs :
	doxygen doxygen.conf
	cd docs/latex && make pdf
	cd ../..
	mv docs/latex/refman.pdf cmatrix.pdf
	mv cmatrix.pdf docs
	clear

.PHONY : all test main clean_obj clean_exe clean docs