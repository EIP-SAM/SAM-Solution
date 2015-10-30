#include "Entity.hpp"
#include <QDebug>
#include <QLibraryInfo>

Entity::Entity()
{
  db = new QSqlDatabase();
}

Entity::~Entity()
{
  delete db;
}

bool Entity::Connect()
{
  *db = QSqlDatabase::addDatabase("QMYSQL");
  db->setHostName("127.0.0.1");
  db->setDatabaseName("test");
  db->setUserName("root");
  db->setPassword("root");
  return db->open();
}
