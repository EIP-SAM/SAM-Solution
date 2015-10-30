#include <QApplication>
#include "Entity.hpp"
#include <QDebug>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  Entity entity;

  if (entity.Connect())
    {
      qDebug() << "SUCCESS";
    }
  else
    {
      qDebug() << "FAIL";
    }

  return app.exec();
}
