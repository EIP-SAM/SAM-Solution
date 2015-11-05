#include <QDebug>
#include <iostream>
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

//
// Establish a new connection to the database
// using a specific driver
//
bool Entity::connect()
{
    *_db = QSqlDatabase::addDatabase("QMYSQL");
    _db->setHostName("127.0.0.1");
    _db->setDatabaseName("test");
    _db->setUserName("root");
    _db->setPassword("root");
    return _db->open();
}

//
// Get the table attribute
//
QString Entity::getTable() const
{
    return _table;
}

//
// Set the table attribute
//
void Entity::setTable(QString newTable)
{
    _table = newTable;
}

//
// Perform the save, by updating the row
// or by inserting the new data
//
bool Entity::save()
{
    QSqlQuery query;

    if(!this->startConnection())
	return false;

    if (this->_propertiesValue->at(0).compare("-1") == 0)
	query = this->prepareInsert();
    else
	query = this->prepareUpdate();

    return (query.exec());
}

//
// Prepare the query for perform an Insert
//
QSqlQuery Entity::prepareInsert() const
{
    QSqlQuery queryObj;
    QString query = "INSERT INTO " + this->_table;
    QString fields;
    QString values;

    for (unsigned int i = 1; i < this->_propertiesName->size(); ++i)
    {
	fields += this->_propertiesName->at(i);
	if (i < this->_propertiesName->size() - 1)
	    fields += ", ";

	values += ":" + this->_propertiesName->at(i);
	if (i < this->_propertiesValue->size() - 1)
	    values += ", ";
    }

    queryObj.prepare(query + " (" + fields + ") VALUES (" + values + ");");

    for (unsigned int i = 1; i < this->_propertiesValue->size(); ++i)
    {
	queryObj.bindValue(":" + this->_propertiesName->at(i), this->_propertiesValue->at(i));
    }

    return queryObj;
}

//
// Prepare the query for perform an Update
//
QSqlQuery Entity::prepareUpdate() const
{
    QSqlQuery queryObj;
    QString query = "UPDATE " + this->_table;
    QString fields;
    QString where = "WHERE id = '" + this->_propertiesValue->at(0)  + "'";

    for (unsigned int i = 0; i < this->_propertiesName->size(); ++i)
    {
	fields += this->_propertiesName->at(i) + " = :" + this->_propertiesName->at(i);
	if (i < this->_propertiesName->size() - 1)
	    fields += ", ";
    }

    queryObj.prepare(query + " SET " + fields + " " + where + ";");

    for (unsigned int i = 0; i < this->_propertiesValue->size(); ++i)
    {
	queryObj.bindValue(":" + this->_propertiesName->at(i), this->_propertiesValue->at(i));
    }

    return queryObj;
}

//
// Start a connection with the database
// ONLY if there is no current connection
//
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

//
// Init the two member vectors with all
// attribute's names and values
//
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

//
// Send a query request to delete data
//
bool Entity::deleteQuery(QueryBuilder *builder)
{
    QSqlRecord recQuery;

    if(!this->startConnection())
	return false;
    return (builder->build()->exec());
}

//
// Get a new fresh instance of the
// QueryBuilder, set with Entity data
//
QueryBuilder *Entity::getQueryBuilder()
{
    return (new QueryBuilder(this->_table, this->_db));
}
