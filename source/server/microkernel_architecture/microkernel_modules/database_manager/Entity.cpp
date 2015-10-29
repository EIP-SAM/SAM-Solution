#include "Entity.hpp"
#include <QDebug>
#include <QLibraryInfo>
Entity::Entity()
{
}

Entity::~Entity()
{
}

bool Entity::Connect()
{
  qDebug() << QLibraryInfo::location(QLibraryInfo::PluginsPath);
  db = new QSqlDatabase();
  *db = QSqlDatabase::addDatabase("QMYSQL");
  db->setHostName("127.0.0.1");
  db->setDatabaseName("test");
  db->setUserName("root");
  db->setPassword("");
  return db->open();
}
