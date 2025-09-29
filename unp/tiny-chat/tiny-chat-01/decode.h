#ifndef DECODE_H_
#define DECODE_H_

#include <event2/bufferevent.h>
#include <string>

std::string decode(bufferevent* bev);

#endif
