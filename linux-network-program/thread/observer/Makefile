OBJ = observer
SRC = observer.cc

CC       = clang++
CC_FLAGS = -Wall -Werror

all: ${OBJ}

$(OBJ): $(SRC) 
	$(CC) $(CC_FLAGS) $(SRC) -o $(OBJ)

clean:
	rm -rf $(OBJ)
