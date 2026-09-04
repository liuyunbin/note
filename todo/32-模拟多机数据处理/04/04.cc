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

std::vector<int> creat_data() {
    std::vector<int> data;

    std::srand(std::time(nullptr));
    for (int i = 0; i != 1000; ++i) data.push_back(std::rand() % 1000);

    return data;
}

bool compare(const std::vector<int>& left, const std::vector<int>& right) {
    return left.back() < right.back();
}

bool compare_less(const std::vector<int>& left, const std::vector<int>& right) {
    return left.back() > right.back();
}

void log_init(int argc, char* argv[]) {
    FLAGS_logtostderr = true;
    FLAGS_colorlogtostderr = true;
    google::InitGoogleLogging(argv[0]);
}

int main(int argc, char* argv[]) {
    const int N = 4;
    const int M = 10;

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

    std::vector<int> client_socket;
    for (int i = 0; i != N; ++i) {
        int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        client_socket.push_back(sock);
        connect(sock, reinterpret_cast<struct sockaddr*>(&server_addr),
                static_cast<socklen_t>(sizeof server_addr));

        std::vector<std::vector<int>> data;
        for (int j = 0; j != M; ++j) data.push_back(creat_data());
        std::vector<int> result;

        for (int j = 0; j != M; ++j) std::sort(data[j].begin(), data[j].end());

        std::make_heap(data.begin(), data.end(), compare);
        for (;;) {
            if (data.empty()) break;
            auto temp = data[0];
            std::pop_heap(data.begin(), data.end(), compare);
            data.pop_back();
            result.push_back(temp.back());
            temp.pop_back();
            if (!temp.empty()) {
                data.push_back(temp);
                std::push_heap(data.begin(), data.end(), compare);
            }
        }
        {
            auto temp = std::to_string(result.size());
            write(sock, temp.data(), temp.size() + 1);
        }
        for (auto v : result) {
            auto temp = std::to_string(v);
            write(sock, temp.data(), temp.size() + 1);
        }
        shutdown(sock, SHUT_WR);
    }

    std::vector<std::vector<int>> data;

    long long size = 0;

    std::vector<int> server_socket;
    for (int i = 0; i != N; ++i) {
        int con_socket = accept(listen_socket, NULL, NULL);
        server_socket.push_back(con_socket);
        {
            std::string temp_str;
            for (;;) {
                char ch;
                read(con_socket, &ch, sizeof(ch));
                if (ch == '\0') {
                    size += std::atoll(temp_str.data());
                    break;
                }
                temp_str.push_back(ch);
            }
        }
        std::vector<int> temp_data;

        for (;;) {
            std::string temp_str;
            char ch;
            if (read(con_socket, &ch, sizeof(ch)) == 0) break;
            temp_str.push_back(ch);
            for (;;) {
                read(con_socket, &ch, sizeof(ch));
                if (ch == '\0') {
                    temp_data.push_back(std::atoi(temp_str.data()));
                    break;
                }
                temp_str.push_back(ch);
            }
        }
        data.push_back(temp_data);
    }

    long long k = 0;
    std::make_heap(data.begin(), data.end(), compare_less);
    for (;;) {
        if (data.empty()) break;
        auto temp = data[0];
        std::pop_heap(data.begin(), data.end(), compare_less);
        data.pop_back();
        ++k;
        auto v = std::to_string(temp.back());
        write(server_socket[N * k / size], v.data(), v.size() + 1);
        temp.pop_back();
        if (!temp.empty()) {
            data.push_back(temp);
            std::push_heap(data.begin(), data.end(), compare_less);
        }
    }

    for (int i = 0; i != N; ++i) close(server_socket[i]);

    for (int i = 0; i != N; ++i) {
        for (;;) {
            char ch;
            if (read(client_socket[i], &ch, sizeof(ch)) == 0) break;
            std::string str;
            str.push_back(ch);
            for (;;) {
                read(client_socket[i], &ch, sizeof(ch));
                if (ch == '\0') {
                    LOG(INFO) << i + 1 << " " << str;
                    break;
                }
                str.push_back(ch);
            }
        }
    }

    return 0;
}
