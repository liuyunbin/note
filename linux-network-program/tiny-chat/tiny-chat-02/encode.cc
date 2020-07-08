
#include "encode.h"

#include "tiny-chat.h"

std::string encode(const std::string& str) {
  char data[PRE_SIZE + 1];
  snprintf(data, sizeof(data), "%0*lu", PRE_SIZE, str.size());
  return data + str;
}

