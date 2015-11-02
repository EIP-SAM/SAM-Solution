#include <QApplication>
#include "UsersEntity.hpp"
#include <QDebug>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  UsersEntity user;

  user.setLogin("bernar_w");
  user.setPassword("test");

  if (user.save())
      qDebug() << "SAVE SUCCESS";
  else
      qDebug() << "SAVE FAIL";
  user.where("login", "=", "claire");

  return 0;
}
