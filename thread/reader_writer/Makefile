OBJ1=test_reader_writer_and_reader_first
SRC1=test_reader_writer_and_reader_first.cc

OBJ2=test_reader_writer_and_writer_first
SRC2=test_reader_writer_and_writer_first.cc

CC       = clang++
CC_FLAGS = -Wall -Werror
LIBS     = -lpthread

all: $(OBJ1) $(OBJ2)

$(OBJ1): $(SRC1)
	$(CC) $(CC_FLAGS) $(LIBS) $(SRC1) -o $(OBJ1)

$(OBJ2): $(SRC2)
	$(CC) $(CC_FLAGS) $(LIBS) $(SRC2) -o $(OBJ2)

clean:
	rm -rf $(OBJ1) $(OBJ2)
