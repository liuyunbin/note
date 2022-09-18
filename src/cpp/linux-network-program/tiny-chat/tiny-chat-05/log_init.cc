
#include "log_init.h"

void log_init(int* argc, char** argv[]) {
  google::SetUsageMessage("This is tiny chat tutorial");
  google::SetVersionString("0.0.1");

  FLAGS_logtostderr = true;
  FLAGS_colorlogtostderr = true;
  google::ParseCommandLineFlags(argc, argv, true);
  google::InitGoogleLogging((*argv)[0]);
}
