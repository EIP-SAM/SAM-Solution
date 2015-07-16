//
// HelloWorld.hpp for SAM-Solution
//
// Made by Nicolas Chauvin
// Email <chauvin.nico@gmail.com>
//
// Started on  Thu Jul 16 20:47:08 2015 Nicolas Chauvin
// Last update Thu Jul 16 21:01:33 2015 Nicolas Chauvin
//

#include <QDebug>

class HelloWorld
{
public:
  static void sayHello()
  {
    qDebug() << "Hello world !";
  }
};
