OBJ = test
SRC = test.cc

CC       = clang++
CC_FLAGS = -Wall -Werror
LIBS     = -lpthread


all: ${OBJ}

$(OBJ): $(SRC) 
	$(CC) $(CC_FLAGS) $(LIBS) $(SRC) -o $(OBJ)

clean:
	rm -rf $(OBJ)
