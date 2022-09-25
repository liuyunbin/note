
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
#include <utility>

#include "chat.heartbeat.pb.h"
#include "chat.message_unit.pb.h"
#include "decode.h"
#include "encode.h"
#include "log_init.h"
#include "tiny-chat.h"

std::unordered_map<struct bufferevent *, std::pair<std::string, int>> client;

void read_callback(struct bufferevent *bev, void *arg) {
    for (;;) {
        std::string message = decode(bev);

        if (message.empty()) return;

        switch (message[0]) {
            case REQUEST_STR: {
                message = message.substr(1);

                LOG(INFO) << client[bev].first << " " << message;

                std::string ack_message = encode(std::string(1, RESPONSE_STR));

                bufferevent_write(bev, ack_message.data(), ack_message.size());

                chat::message_unit msg;
                msg.set_user(client[bev].first);
                msg.set_data(message);

                msg.SerializeToString(&message);

                message = encode(REQUEST_STR + message);

                for (auto it = client.begin(); it != client.end(); ++it)
                    if (it->first != bev)
                        bufferevent_write(it->first, message.data(),
                                          message.size());
                break;
            }
            case HEARTBEAT_STR: {
                chat::heartbeat msg;
                msg.ParseFromString(message.substr(1));

                client[bev].second = msg.time();

                break;
            }
            default: {
                LOG(ERROR) << "BAD MESSAGE";
                break;
            }
        }
    }
}

void event_callback(struct bufferevent *bev, short events, void *arg) {
    if (events & BEV_EVENT_EOF) {
        LOG(INFO) << "client " << client[bev].first << " quit";
        client.erase(bev);
        bufferevent_free(bev);
        LOG(INFO) << "current client count: " << client.size();
    } else if (events & BEV_EVENT_ERROR) {
        PLOG(ERROR) << client[bev].first;
        client.erase(bev);
        bufferevent_free(bev);
        LOG(INFO) << "current client count: " << client.size();
    }
}

void accept_callback(struct evconnlistener *listener, int sock,
                     struct sockaddr *addr, int len, void *arg) {
    auto addr_in = reinterpret_cast<struct sockaddr_in *>(addr);
    char buf[32];
    inet_ntop(AF_INET, &addr_in->sin_addr, buf, static_cast<socklen_t>(len));

    std::string message =
        std::string(buf) + ":" + std::to_string(ntohs(addr_in->sin_port));
    LOG(INFO) << "new connection from " << message;

    struct bufferevent *bev = bufferevent_socket_new(
        evconnlistener_get_base(listener), sock, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setwatermark(bev, EV_READ, PRE_SIZE, 0);

    client[bev] = std::make_pair(message, time(NULL));

    LOG(INFO) << "current client count: " << client.size();

    bufferevent_setcb(bev, read_callback, NULL, event_callback, NULL);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void heartbeat_callback(int fd, short events, void *arg) {
    auto it = client.begin();
    while (it != client.end()) {
        int now = time(NULL);
        if (now - HEARTBEAT_SERVER_TIME > it->second.second) {
            LOG(WARNING) << it->second.first << " maybe lost, delete";
            auto bev = it->first;
            it = client.erase(it);
            bufferevent_free(bev);
        } else {
            ++it;
        }
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

    LOG(INFO) << "server ip: " << server_ip << " port: " << server_port;

    auto base = event_base_new();

    auto signal_event = evsignal_new(base, SIGPIPE, signal_callback, NULL);
    evsignal_add(signal_event, NULL);

    auto heartbeat_event =
        event_new(base, -1, EV_PERSIST, heartbeat_callback, NULL);
    struct timeval tv = {HEARTBEAT_CLIENT_TIME, 0};
    event_add(heartbeat_event, &tv);

    auto listener_event = evconnlistener_new_bind(
        base, accept_callback, NULL, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
        -1, reinterpret_cast<struct sockaddr *>(&server_addr),
        sizeof(server_addr));

    PCHECK(listener_event != NULL);
    event_base_dispatch(base);
}

int main(int argc, char *argv[]) {
    log_init(&argc, &argv);
    run(argc, argv);
    return 0;
}
