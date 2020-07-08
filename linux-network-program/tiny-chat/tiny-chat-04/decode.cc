
#include "decode.h"

#include "tiny-chat.h"

#include <event2/buffer.h>

std::string decode(bufferevent* bev) {
  auto input = bufferevent_get_input(bev);

  char* st = reinterpret_cast<char*>(evbuffer_pullup(input, PRE_SIZE));
  size_t message_len = 0;

  for (int i = 0; i != PRE_SIZE; ++i)
    message_len = message_len * 10 + static_cast<size_t>(st[i] - '0');

  if (evbuffer_get_length(input) < message_len + PRE_SIZE) return std::string();
  char message[MESSAGE_MAX];
  bufferevent_read(bev, message, PRE_SIZE);
  bufferevent_read(bev, message, message_len);
  return std::string(message, message_len);
}

