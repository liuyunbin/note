#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <strings.h>
#include <sys/socket.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <glog/logging.h>

std::vector<int> creat_data() {
  std::vector<int> data;

  std::srand(std::time(nullptr));
  for (int i = 0; i != 10000; ++i) data.push_back(std::rand() % 100);

  return data;
}

void log_init(int argc, char* argv[]) {
  FLAGS_logtostderr = true;
  FLAGS_colorlogtostderr = true;
  google::InitGoogleLogging(argv[0]);
}

bool compare(const std::vector<std::pair<int, std::string>>& left,
             const std::vector<std::pair<int, std::string>>& right) {
  return left.back() < right.back();
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

    std::vector<int> result = creat_data();

    for (auto v : result) {
      auto temp = std::to_string(v);
      write(sock, temp.data(), temp.size() + 1);
    }
    write(sock, "\n", 1);
  }

  std::vector<int> server_client_socket;

  for (int i = 0; i != N; ++i) {
    int con_socket = accept(listen_socket, NULL, NULL);
    server_client_socket.push_back(con_socket);
  }

  for (int i = 0; i != N; ++i) {
    for (;;) {
      std::string str;
      char ch;
      read(server_client_socket[i], &ch, sizeof(ch));
      if (ch == '\n') break;
      str.push_back(ch);
      for (;;) {
        read(server_client_socket[i], &ch, sizeof(ch));
        if (ch == '\0') {
          int index = std::hash<std::string>()(str) % N;
          write(server_client_socket[index], str.data(), str.size() + 1);
          break;
        }
        str.push_back(ch);
      }
    }
  }

  for (int i = 0; i != N; ++i) shutdown(server_client_socket[i], SHUT_WR);

  for (int i = 0; i != N; ++i) {
    std::map<std::string, int> m;
    for (;;) {
      std::string str;
      char ch;
      if (read(client_socket[i], &ch, sizeof(ch)) == 0) break;
      str.push_back(ch);
      for (;;) {
        read(client_socket[i], &ch, sizeof(ch));
        if (ch == '\0') {
          ++m[str];
          break;
        }
        str.push_back(ch);
      }
    }
    std::vector<std::pair<int, std::string>> temp;
    for (auto it = m.begin(); it != m.end(); ++it)
      temp.push_back(std::make_pair(it->second, it->first));
    std::sort(temp.begin(), temp.end());
    for (int j = 0; j != static_cast<int>(temp.size()) && j != M; ++j) {
      write(client_socket[i], temp[j].second.data(), temp[j].second.size() + 1);
      auto v = std::to_string(temp[j].first);
      write(client_socket[i], v.data(), v.size() + 1);
    }
    close(client_socket[i]);
  }

  std::vector<std::vector<std::pair<int, std::string>>> data;

  for (int i = 0; i != N; ++i) {
    std::vector<std::pair<int, std::string>> temp_data;
    for (;;) {
      std::string str_str;
      std::string str_int;
      char ch;
      if (read(server_client_socket[i], &ch, sizeof(ch)) == 0) break;
      str_str.push_back(ch);
      for (;;) {
        read(server_client_socket[i], &ch, sizeof(ch));
        if (ch == '\0') break;
        str_str.push_back(ch);
      }
      for (;;) {
        read(server_client_socket[i], &ch, sizeof(ch));
        if (ch == '\0') break;
        str_int.push_back(ch);
      }
      temp_data.push_back(std::make_pair(std::atoi(str_int.data()), str_str));
    }
    data.push_back(temp_data);
  }

  std::make_heap(data.begin(), data.end(), compare);
  for (int i = 0; i != M; ++i) {
    if (data.empty()) break;
    auto temp = data[0];
    std::pop_heap(data.begin(), data.end(), compare);
    data.pop_back();

    LOG(INFO) << i + 1 << "th " << temp.back().second << " "
              << temp.back().first;

    temp.pop_back();
    if (!temp.empty()) {
      data.push_back(temp);
      std::push_heap(data.begin(), data.end(), compare);
    }
  }

  return 0;
}
