
#include <arpa/inet.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <netinet/in.h>
#include <signal.h>
#include <strings.h>
#include <unistd.h>

#include <string>
#include <unordered_map>

std::unordered_map<struct bufferevent *, std::string> client;

void read_callback(struct bufferevent *bev, void *arg) {
    auto input = bufferevent_get_input(bev);
    auto output = bufferevent_get_output(bev);
    evbuffer_add_buffer(output, input);
}

void write_complete_callback(struct bufferevent *bev, void *arg) {
    printf("send message to %s success\n", client[bev].data());
    client.erase(bev);
    bufferevent_free(bev);
    printf("current client count: %lu\n", client.size());
}

void event_callback(struct bufferevent *bev, short events, void *arg) {
    if (events & BEV_EVENT_EOF) {
        printf("revecive EOF from %s\n", client[bev].data());

        auto output = bufferevent_get_output(bev);
        if (evbuffer_get_length(output) == 0) {
            client.erase(bev);
            bufferevent_free(bev);
            printf("current client count: %lu\n", client.size());
            return;
        }
        printf("try to send message to %s\n", client[bev].data());
        bufferevent_setcb(bev, NULL, write_complete_callback, event_callback,
                          NULL);
    } else if (events & BEV_EVENT_ERROR) {
        perror("");
        client.erase(bev);
        bufferevent_free(bev);
        printf("current client count: %lu\n", client.size());
    } else if (events & BEV_EVENT_TIMEOUT) {
        if (events & BEV_EVENT_READING)
            printf("read timeout from %s\n", client[bev].data());
        if (events & BEV_EVENT_WRITING)
            printf("write timeout to %s\n", client[bev].data());
        client.erase(bev);
        bufferevent_free(bev);
        printf("current client count: %lu\n", client.size());
    }
}

void accept_callback(struct evconnlistener *listener, int sock,
                     struct sockaddr *addr, int len, void *arg) {
    auto addr_in = reinterpret_cast<struct sockaddr_in *>(addr);
    char buf[32];
    inet_ntop(AF_INET, &addr_in->sin_addr, buf, static_cast<socklen_t>(len));

    std::string message =
        std::string(buf) + ":" + std::to_string(ntohs(addr_in->sin_port));
    printf("new connection from %s\n", message.data());

    auto bev = bufferevent_socket_new(evconnlistener_get_base(listener), sock,
                                      BEV_OPT_CLOSE_ON_FREE);

    client[bev] = message;

    printf("current client count: %lu\n", client.size());

    bufferevent_setwatermark(bev, EV_READ, 0,
                             1024 * 1024);  // 设置读的高水位值，避免恶意用户

    struct timeval tv = {1, 0};
    bufferevent_set_timeouts(bev, NULL, &tv);
    bufferevent_setcb(bev, read_callback, NULL, event_callback, NULL);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void signal_callback(int fd, short event, void *arg) {
    if (fd == SIGPIPE) printf("catch SIGPIPE, ignore\n");
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

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    printf("server port = %d\n", server_port);

    auto base = event_base_new();
    auto signal_event = evsignal_new(base, SIGPIPE, signal_callback, NULL);
    evsignal_add(signal_event, NULL);

    auto listener_event = evconnlistener_new_bind(
        base, accept_callback, NULL, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
        -1, (struct sockaddr *)(&server_addr), sizeof(server_addr));

    event_base_dispatch(base);

    event_free(signal_event);
    evconnlistener_free(listener_event);
    event_base_free(base);

    return 0;
}
