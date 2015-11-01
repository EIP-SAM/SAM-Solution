#include "Entity.hpp"

Entity::Entity()
{
  db = new QSqlDatabase();
}

Entity::~Entity()
{
  if (db->isOpen())
    db->close();
  delete db;
}

bool		Entity::connect()
{
  *db = QSqlDatabase::addDatabase("QMYSQL");
  db->setHostName("127.0.0.1");
  db->setDatabaseName("test");
  db->setUserName("root");
  db->setPassword("root");
  return db->open();
}

std::string	Entity::getTable() const
{
  return this->table;
}

void		Entity::setTable(std::string newTable)
{
  this->table = newTable;
}

bool		Entity::save()
{
  // const QMetaObject* metaObject = obj->metaObject();

  // QStringList properties;
  // for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
  //   properties << QString::fromLatin1(metaObject->property(i).name());

  return (true);
}
