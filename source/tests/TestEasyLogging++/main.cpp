#include <unistd.h>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

/*
** Set the configuration file and set it to all loggers
*/
int main(int ac, char **av)
{
  START_EASYLOGGINGPP(ac, av);

  el::Configurations conf("../log.conf");
  el::Loggers::reconfigureAllLoggers(conf);

  for (int i = 0; i < 10; ++i) {
    sleep(1);
    LOG(INFO) << "EasyLogging++ INFO";
    LOG(DEBUG) << "EasyLogging++ DEBUG";
  }
  return 0;
}
