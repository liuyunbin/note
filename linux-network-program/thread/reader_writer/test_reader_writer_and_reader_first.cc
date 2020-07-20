
#include "reader_writer_and_reader_first.h"

#include <iostream>

static void  input();
static void output();

int main() {
  for (;;) {
    input();
    output();
  }
  return 0;
}

static ReaderWriterAndReaderFirst<int> reader_writer;
static int data = 0;

static void input() {
  std::cout << "reader writer, reader first"        << std::endl << std::endl;
  std::cout << "Please input : 1 ReaderBlocking"    << std::endl;
  std::cout << "               2 ReaderNonBlocking" << std::endl;
  std::cout << "               3 WriterBlocking"    << std::endl;
  std::cout << "               4 WriterNonBlocking" << std::endl;
  std::cout << "input: ";
  char ch = std::cin.peek();
  while (ch == ' ' || ch == '\t') {
    std::cin.get();
    ch = std::cin.peek();
  }
  if (ch == '\n') {
    std::cin.get();
    return ;
  }
  switch (std::cin.get()) {
    case '1':
      reader_writer.ReaderBlocking();
      break;
    case '2':
      reader_writer.ReaderNonBlocking();
      break;
    case '3':
      reader_writer.WriterBlocking(++data);
      break;
    case '4':
      reader_writer.WriterNonBlocking(++data);
      break;
    default:
      std::cout << "input error" << std::endl;
      break;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void output() {
  reader_writer.output_log(std::cout);
}
