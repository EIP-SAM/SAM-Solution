//
// main.cpp for SAM-Solution
//
// Made by Nicolas Chauvin
// Email <chauvin.nico@gmail.com>
//
// Started on  Wed Jul 15 01:14:40 2015 Nicolas Chauvin
// Last update Thu Jul 16 21:12:02 2015 Nicolas Chauvin
//

#include "HelloWorld.hpp"

int main(int ac, char **av)
{
  HelloWorld::sayHello();
  qDebug() << "I'm the user client";
  return (0);
}
