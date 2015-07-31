//
// HelloWorld.hpp for SAM-Solution
//
// Made by Nicolas Chauvin
// Email <chauvin.nico@gmail.com>
//
// Started on  Thu Jul 16 20:47:08 2015 Nicolas Chauvin
// Last update Fri Jul 31 10:00:18 2015 Nicolas Chauvin
//

#include <QDebug>

class HelloWorld
{
public:
  static void sayHello()
  {
    qDebug() << "Shared code between all sam sub-projects : Hello world !";
  }
};
