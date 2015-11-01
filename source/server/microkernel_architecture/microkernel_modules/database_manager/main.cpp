#include <QApplication>
#include "UsersEntity.hpp"
#include <QDebug>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  UsersEntity user;

  if (user.connect())
    {
      qDebug() << "CONNECTION SUCCESS";

      user.setId(42);
      user.setLogin("bernar_w");
      user.setPassword("test");

      if (user.save())
	qDebug() << "SAVE SUCCESS";
      else
	qDebug() << "SAVE FAIL";
    }
  else
    {
      qDebug() << "CONNECTION FAIL";
    }

  return 0;
}
