#include "Entity.hpp"
#include <QDebug>
#include <iostream>

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

QString		Entity::getTable() const
{
  return this->table;
}

void		Entity::setTable(QString newTable)
{
  this->table = newTable;
}

bool		Entity::save()
{
  const QMetaObject *metaobject = this->metaObject();
  int count = metaobject->propertyCount();
  int offset =  metaobject->propertyOffset();


  for (int i = offset; i < count; ++i) {
    QMetaProperty metaproperty = metaobject->property(i);

    const char *name = metaproperty.name();

    QVariant value = this->property(name);
    QString valueString = value.toString();
  }

  return (true);
}
