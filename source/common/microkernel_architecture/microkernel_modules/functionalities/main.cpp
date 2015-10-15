#include <unistd.h>
#include <iostream>
#include <QThread>
#include "FunctionalitiesManager.hpp"

int main()
{
  FunctionalitiesManager *manager;

  manager = new FunctionalitiesManager();

  manager->init();
  delete manager;
  return (0);
}
