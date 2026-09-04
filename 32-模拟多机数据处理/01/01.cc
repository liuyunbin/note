#include <arpa/inet.h>
#include <glog/logging.h>
#include <netinet/in.h>
#include <signal.h>
#include <strings.h>
#include <sys/socket.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "tiny-huge-number-calculator.h"

std::vector<int> creat_data() {
    std::vector<int> data;

    std::srand(std::time(nullptr));
    for (int i = 0; i != 10; ++i)
        for (int j = 0; j != 10000; ++j) data.push_back(std::rand());

    return data;
}

void log_init(int argc, char* argv[]) {
    FLAGS_logtostderr = true;
    FLAGS_colorlogtostderr = true;
    google::InitGoogleLogging(argv[0]);
}

int main(int argc, char* argv[]) {
    const int N = 4;

    log_init(argc, argv);

    const char* server_ip = "127.0.0.1";
    uint16_t server_port = 6666;

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int opt = 1;
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    bind(listen_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
         static_cast<socklen_t>(sizeof server_addr));
    listen(listen_socket, 5);

    for (int i = 0; i != N; ++i) {
        int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(client_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
                static_cast<socklen_t>(sizeof server_addr));

        auto data = creat_data();

        std::string result = std::to_string(data.size());
        write(client_socket, result.data(), result.size());
        write(client_socket, "", 1);

        result = "0";
        for (auto v : data)
            result = add_huge_numbers(result, std::to_string(v));
        write(client_socket, result.data(), result.size());
        close(client_socket);
    }

    std::string result = "0";
    std::string size = "0";

    for (int i = 0; i != N; ++i) {
        int con_socket = accept(listen_socket, NULL, NULL);
        std::string temp;
        for (;;) {
            char ch;
            read(con_socket, &ch, sizeof(ch));
            if (ch == '\0') {
                size = add_huge_numbers(size, temp);
                LOG(INFO) << "the " << i + 1 << "th size " << temp;
                temp.clear();
                break;
            }
            temp.push_back(ch);
        }
        for (;;) {
            char ch;
            if (read(con_socket, &ch, sizeof(ch)) == 0) {
                result = add_huge_numbers(result, temp);
                LOG(INFO) << "the " << i + 1 << "th data " << temp;
                break;
            }
            temp.push_back(ch);
        }
    }

    LOG(INFO) << "data    = " << result;
    LOG(INFO) << "size    = " << size;
    LOG(INFO) << "average = " << div_huge_numbers(result, size);

    return 0;
}
