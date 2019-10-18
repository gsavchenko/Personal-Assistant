# compiler to use
CC = gcc

# folders to build to
BIN = ./bin/
SRC = ./src/

# Message to pass
FILE_NAME = "example_input.txt"

# compiler flags
CFLAGS = -Wall -g -pedantic -std=c99

# library flags
LFLAGS = -L./lib/ -lLinkedList

# location of header files
INCLUDES = -Iinclude

# source C files
MAIN_SRCS = $(SRC)main.c $(SRC)integer.c $(SRC)binaryTree.c $(SRC)conversation.c
TEST_SRCS = $(SRC)testMain.c $(SRC)integer.c $(SRC)binaryTree.c

# object C files ending in .o
MAIN_OBJS = $(MAIN_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# executable files
MAIN = main
TEST = test

# make commands
# build all files
all:	one two
one: 	$(MAIN_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN)$(MAIN) $(MAIN_OBJS)
two:	$(TEST_OBJS)	
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN)$(TEST) $(TEST_OBJS)

# compile object files
.c.o:	
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
# run main
run:
	$(BIN)$(MAIN) ${FILE_NAME}
# run test
test:
	$(BIN)$(TEST)
# remove build files
clean:	
	$(RM) $(SRC)*.o *~ $(BIN)*