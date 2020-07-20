
#include "producer_consumer.h"

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

static ProducerConsumer<int> producer_consumer;

static void input() {
  static int data = 0;
  
  std::cout << "Please input : 1 ProducerBlocking"    << std::endl;
  std::cout << "               2 ProducerNonBlocking" << std::endl;
  std::cout << "               3 ConsumerBlocking"    << std::endl;
  std::cout << "               4 ConsumerNonBlocking" << std::endl;
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
      producer_consumer.ProducerBlocking(++data);
      break;
    case '2':
      producer_consumer.ProducerNonBlocking(++data);
      break;
    case '3':
      producer_consumer.ConsumerBlocking();
      break;
    case '4':
      producer_consumer.ConsumerNonBlocking();
      break;
    default:
      std::cout << "input error" << std::endl;
      break;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void output() {
  producer_consumer.output_log(std::cout);
}
