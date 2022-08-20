OBJ = test_producer_consumer
SRC = test_producer_consumer.cc

CC       = clang++
CC_FLAGS = -Wall -Werror
LIBS     = -lpthread

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CC_FLAGS) $(LIBS) $(SRC) -o $(OBJ)

clean:
	rm -rf $(OBJ)
