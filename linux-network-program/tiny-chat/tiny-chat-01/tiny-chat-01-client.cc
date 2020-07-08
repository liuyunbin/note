
#include "log_init.h"

#include "decode.h"
#include "encode.h"
#include "tiny-chat.h"

#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

void std_read_callback(struct bufferevent *bev, void *arg) {
  auto input = bufferevent_get_input(bev);
  size_t len = evbuffer_get_length(input);

  if (len == 1 || len > USER_MESSAGE_MAX) {
    if (len > USER_MESSAGE_MAX)
      LOG(ERROR) << "message can't over " << USER_MESSAGE_MAX;
    evbuffer_drain(input, len);
    return;
  }

  char buf[MESSAGE_MAX];
  bufferevent_read(bev, buf, sizeof(buf));
  std::string data = encode(std::string(buf, len));
  auto net_bev = reinterpret_cast<struct bufferevent *>(arg);
  bufferevent_write(net_bev, data.data(), data.size());
}

void net_read_callback(struct bufferevent *net_bev, void *arg) {
  std::string message = decode(net_bev);

  if (message.empty()) return;

  auto std_bev = reinterpret_cast<struct bufferevent *>(arg);
  bufferevent_write(std_bev, message.data(), message.size());
}

void std_event_callback(struct bufferevent *bev, short events, void *arg) {
  if (events & BEV_EVENT_ERROR) {
    PLOG(ERROR);
    event_base_loopexit(bufferevent_get_base(bev), NULL);
  } else if (events & BEV_EVENT_EOF) {
    LOG(WARNING) << "client quit";
    event_base_loopexit(bufferevent_get_base(bev), NULL);
  }
}

void net_event_callback(struct bufferevent *bev, short events, void *arg) {
  if (events & BEV_EVENT_CONNECTED) {
    LOG(INFO) << "connection success.\n";
  } else if (events & BEV_EVENT_ERROR) {
    PLOG(ERROR);
    event_base_loopexit(bufferevent_get_base(bev), NULL);
  } else if (events & BEV_EVENT_EOF) {
    LOG(ERROR) << "server quit accident...";
    event_base_loopexit(bufferevent_get_base(bev), NULL);
  }
}

void signal_callback(int fd, short event, void *arg) {
  if (fd == SIGPIPE) LOG(WARNING) << "catch SIGPIPE, ignore";
}

void run(int argc, char *argv[]) {
  const char *server_ip = SERVER_IP;
  uint16_t server_port = SERVER_PORT;

  if (argc > 1) server_ip = argv[1];
  if (argc > 2) server_port = static_cast<uint16_t>(atoi(argv[2]));

  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof server_addr);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(server_port);
  inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

  auto base = event_base_new();

  auto signal_event = evsignal_new(base, SIGPIPE, signal_callback, NULL);
  evsignal_add(signal_event, NULL);

  int fd = STDIN_FILENO;
  evutil_make_socket_nonblocking(fd);

  auto net_bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
  auto std_bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

  bufferevent_setwatermark(net_bev, EV_READ, PRE_SIZE, 0);

  bufferevent_setcb(net_bev, net_read_callback, NULL, net_event_callback,
                    std_bev);
  bufferevent_setcb(std_bev, std_read_callback, NULL, std_event_callback,
                    net_bev);

  bufferevent_enable(net_bev, EV_READ | EV_WRITE);
  bufferevent_enable(std_bev, EV_READ | EV_WRITE);

  LOG(INFO) << "try to connect " << server_ip << ":" << server_port;
  bufferevent_socket_connect(net_bev,
                             reinterpret_cast<struct sockaddr *>(&server_addr),
                             sizeof(server_addr));

  event_base_dispatch(base);
  bufferevent_free(net_bev);
  bufferevent_free(std_bev);
  event_base_free(base);
}

int main(int argc, char *argv[]) {
  log_init(&argc, &argv);
  run(argc, argv);
  return 0;
}
