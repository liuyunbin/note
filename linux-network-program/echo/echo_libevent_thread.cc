
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/thread.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <strings.h>
#include <unistd.h>

#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

std::mutex client_mutex;
std::unordered_map<struct bufferevent *, std::string> client;

std::vector<std::thread> child_thread;
std::vector<struct event_base *> child_base;

void read_callback(struct bufferevent *bev, void *arg) {
  auto input = bufferevent_get_input(bev);
  auto output = bufferevent_get_output(bev);
  evbuffer_add_buffer(output, input);
}

void write_complete_callback(struct bufferevent *bev, void *arg) {
  {
    std::lock_guard<std::mutex> lock(client_mutex);
    printf("send message to %s\n success\n", client[bev].data());
    client.erase(bev);
    printf("current client count: %lu\n", client.size());
  }
  bufferevent_free(bev);
}

void event_callback(struct bufferevent *bev, short events, void *arg) {
  if (events & BEV_EVENT_EOF) {
    auto output = bufferevent_get_output(bev);
    if (evbuffer_get_length(output) == 0) {
      {
        std::lock_guard<std::mutex> lock(client_mutex);
        printf("%s quit\n", client[bev].data());
        client.erase(bev);
        printf("current client count: %lu\n", client.size());
      }
      bufferevent_free(bev);
      return;
    }
    {
      std::lock_guard<std::mutex> lock(client_mutex);
      printf("try to send message to %s\n", client[bev].data());
    }
    bufferevent_setcb(bev, NULL, write_complete_callback, event_callback, NULL);
  } else if (events & BEV_EVENT_ERROR) {
    {
      std::lock_guard<std::mutex> lock(client_mutex);
      perror("");
      client.erase(bev);
      printf("current client count: %lu\n", client.size());
    }
    bufferevent_free(bev);
  } else if (events & BEV_EVENT_TIMEOUT) {
    {
      std::lock_guard<std::mutex> lock(client_mutex);
      if (events & BEV_EVENT_READING)
        printf("read timeout from %s\n", client[bev].data());
      if (events & BEV_EVENT_WRITING)
        printf("write timeout to %s\n", client[bev].data());
      client.erase(bev);
      printf("current client count: %lu\n", client.size());
    }
    bufferevent_free(bev);
  }
}

void thread_function(struct event_base *base) {
  event_base_loop(base, EVLOOP_NO_EXIT_ON_EMPTY);
}

void run_thread(int n) {
  for (int i = 0; i != n; ++i) {
    auto base = event_base_new();
    child_base.push_back(base);
    child_thread.emplace_back(std::thread(thread_function, base));
  }
}

struct event_base *get_next_base() {
  static size_t k = 0;
  if (k == child_base.size())
    k = 0;
  return child_base[k];
}

void accept_callback(struct evconnlistener *listener, int sock, struct sockaddr *addr, int len, void *arg) {
  auto addr_in = reinterpret_cast<struct sockaddr_in *>(addr);
  char buf[32];
  inet_ntop(AF_INET, &addr_in->sin_addr, buf, static_cast<socklen_t>(len));

  std::string message =
      std::string(buf) + ":" + std::to_string(ntohs(addr_in->sin_port));
  printf("new connection from %s\n", message.data());

  auto bev = bufferevent_socket_new(get_next_base(), sock, BEV_OPT_CLOSE_ON_FREE);

  {
    std::lock_guard<std::mutex> lock(client_mutex);
    client[bev] = message;
    printf("current client count: %lu\n", client.size());
  }

  bufferevent_setwatermark(bev, EV_READ, 0, 1024*1024); // 设置读的高水位值，避免恶意用户

  struct timeval tv = {1, 0};
  bufferevent_set_timeouts(bev, NULL, &tv);
  bufferevent_setcb(bev, read_callback, NULL, event_callback, NULL);
  bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void signal_callback(int fd, short event, void *arg) {
  if (fd == SIGPIPE)
    printf("catch SIGPIPE, ignore\n");
}

int main(int argc, char *argv[]) {
  
  if (argc < 2) {
    printf("usage: %s port\n", argv[0]);
    return -1;
  }

  uint16_t server_port = atoi(argv[1]);

  if (server_port <= 0) {
    printf("usage: %s port\n", argv[0]);
    return -1;
  }

  const char *server_ip = "0.0.0.0";

  evthread_use_pthreads();

  run_thread(4);

  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof server_addr);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(server_port);
  inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

  printf("server port: %d\n", server_port);

  auto base = event_base_new();
  auto signal_event = evsignal_new(base, SIGPIPE, signal_callback, NULL);
  evsignal_add(signal_event, NULL);

  auto listener_event = evconnlistener_new_bind(
      base, accept_callback, NULL, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
      -1, (struct sockaddr*)(&server_addr),
      sizeof(server_addr));

  event_base_dispatch(base);

  event_free(signal_event);
  evconnlistener_free(listener_event);
  event_base_free(base);

  return 0;
}

