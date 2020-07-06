
#include <TinyLog/log_stream.h>
#include <TinyLog/logging_async.h>
#include <TinyLog/logging.h>
#include <TinyLog/logger.h>

using namespace TinyLog;

int main() {
  LoggingAsync log("log_name", 1024 * 1024);
  log.start();
  int N = 1024 * 1024;
  char data[] = "1234567890";
  for (int i = 0; i != N; ++i)
    LOG_ERROR << data << data;
  log.stop();
  return 0;
}

