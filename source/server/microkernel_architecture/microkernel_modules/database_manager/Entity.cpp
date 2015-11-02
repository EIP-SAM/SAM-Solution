#include <QDebug>
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include "Entity.hpp"

Entity::Entity()
{
    _db = new QSqlDatabase();
}

Entity::~Entity()
{
    if (_db->isOpen())
	_db->close();
    delete _db;
}

bool Entity::connect()
{
    *_db = QSqlDatabase::addDatabase("QMYSQL");
    _db->setHostName("127.0.0.1");
    _db->setDatabaseName("test");
    _db->setUserName("root");
    _db->setPassword("root");
    return _db->open();
}

QString Entity::getTable() const
{
    return _table;
}

void Entity::setTable(QString newTable)
{
    _table = newTable;
}

bool Entity::save()
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

std::vector<Entity *> Entity::where(QString field, QString comparator, QString value)
{
    QSqlQuery query;
    std::vector<Entity *> result;

    (void) comparator;
    query.prepare("SELECT * FROM " + _table + " WHERE " + field + comparator + " :value");
    query.bindValue(":value", value);
    query.exec();
    std::cout << query.lastError().databaseText().toStdString() << std::endl;
    while (query.next())
    {
	std::cout << query.value(1).toString().toStdString() << std::endl;
	std::cout << query.value(2).toString().toStdString() << std::endl;
    }
    return (result);
}
