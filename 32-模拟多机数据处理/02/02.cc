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
    for (int i = 0; i != 1000; ++i) data.push_back(std::rand());

    return data;
}

bool compare(const std::vector<int>& left, const std::vector<int>& right) {
    return left.back() < right.back();
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

    for (int i = 0; i != N; ++i) {
        int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(client_socket, reinterpret_cast<struct sockaddr*>(&server_addr),
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
            write(client_socket, temp.data(), temp.size() + 1);
        }
        for (auto v : result) {
            auto temp = std::to_string(v);
            write(client_socket, temp.data(), temp.size() + 1);
        }
        close(client_socket);
    }

    std::vector<std::vector<int>> data;

    long long size = 0;

    for (int i = 0; i != N; ++i) {
        int con_socket = accept(listen_socket, NULL, NULL);

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

    // 为求简单，直接存储了所有数据，
    // 实际中可以建立一个结构体，
    // 将数据和 socket 结合起来，
    // 一旦弹出数据，直接从 socket 读入新数据
    long long k = 0;
    std::make_heap(data.begin(), data.end(), compare);
    for (;;) {
        if (data.empty()) break;
        auto temp = data[0];
        std::pop_heap(data.begin(), data.end(), compare);
        data.pop_back();
        ++k;
        if (k == size / 2) {
            LOG(INFO) << "mid: " << temp.back();
            break;
        }
        temp.pop_back();
        if (!temp.empty()) {
            data.push_back(temp);
            std::push_heap(data.begin(), data.end(), compare);
        }
    }

    return 0;
}
