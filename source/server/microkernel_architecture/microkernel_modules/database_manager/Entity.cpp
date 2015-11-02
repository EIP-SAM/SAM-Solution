#include <QDebug>
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include "Entity.hpp"

Entity::Entity()
{
    _db = new QSqlDatabase();
    _propertiesName = NULL;
    _propertiesValue = NULL;
}

Entity::~Entity()
{
    if (_db->isOpen())
	_db->close();

    if (_propertiesName)
	delete _propertiesName;
    if (_propertiesValue)
	delete _propertiesValue;

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

    this->startConnection();

    for (unsigned int i = 0; i < this->_propertiesName->size(); ++i)
    {
	qDebug() << this->_propertiesName->at(i) << " ==> " << this->_propertiesValue->at(i);
    }

    return (true);
}

std::vector<Entity *> Entity::where(QString field, QString comparator, QString value)
{
    QSqlQuery query;
    std::vector<Entity *> result;

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

bool Entity::startConnection()
{
    if (!_db->isOpen())
    {
	if (!this->connect())
	    return false;
	qDebug() << "CONNECTION SUCCESS";
    }
    this->getAllProperties();
    return true;
}

void Entity::getAllProperties()
{
    this->_propertiesName = new std::vector<QString>;
    this->_propertiesValue = new std::vector<QString>;

    const QMetaObject *metaObject = this->metaObject();
    int count = metaObject->propertyCount();
    int offset =  metaObject->propertyOffset();

    for (int i = offset; i < count; ++i) {
	QMetaProperty metaProperty = metaObject->property(i);
	const char *propertyName = metaProperty.name();
	this->_propertiesName->push_back(propertyName);

	QVariant value = this->property(propertyName);
	this->_propertiesValue->push_back(value.toString());
    }
}
