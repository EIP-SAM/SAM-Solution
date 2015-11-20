#include <QDebug>
#include <iostream>
#include "Entity.hpp"

//
// Init attributs
// Create database instance
//
Entity::Entity() : _db(new QSqlDatabase()), _dbType(MYSQL_TYPE), _propertiesName(NULL), _propertiesValue(NULL)
{
}

//
// Close database instance
// Clean object properties
//
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
void Entity::setTable(const QString &newTable)
{
    _table = newTable;
}

//
// Perform the save, by updating the row
// or by inserting the new data
//
bool Entity::save()
{
    QSqlQuery *query;

    if(!startConnection())
	return false;

    if (_propertiesValue->at(0).compare("-1") == 0)
	query = prepareInsert();
    else
	query = prepareUpdate();

    return (query->exec());
}

//
// Prepare the query for perform an Insert
//
QSqlQuery *Entity::prepareInsert() const
{
    AQueryBuilder *builder = this->getQueryBuilder();
    QString fields;
    QString values;

    for (int i = 1; i < _propertiesName->size(); ++i)
    {
	fields += _propertiesName->at(i);
	if (i < _propertiesName->size() - 1)
	    fields += ", ";

	values += ":" + _propertiesName->at(i);
	if (i < _propertiesValue->size() - 1)
	    values += ", ";
    }

    builder->insertQuery(fields, values);

    for (int i = 1; i < _propertiesValue->size(); ++i)
    {
	builder->bindValue(":" + _propertiesName->at(i), _propertiesValue->at(i));
    }

    return builder->build();
}

//
// Prepare the query for perform an Update
//
QSqlQuery *Entity::prepareUpdate() const
{
    AQueryBuilder *builder = this->getQueryBuilder();
    QString fields;
    QString whereClause = "id = '" + _propertiesValue->at(0)  + "'";

    for (int i = 0; i < _propertiesName->size(); ++i)
    {
	fields += _propertiesName->at(i) + " = :" + _propertiesName->at(i);
	if (i < _propertiesName->size() - 1)
	    fields += ", ";
    }

    builder->updateQuery(fields, whereClause);

    for (int i = 0; i < _propertiesValue->size(); ++i)
    {
	builder->bindValue(":" + _propertiesName->at(i), _propertiesValue->at(i));
    }

    return builder->build();
}

//
// Start a connection with the database
// ONLY if there is no current connection
//
bool Entity::startConnection()
{
    if (!_db->isOpen())
    {
	if (!connect())
	    return false;
	qDebug() << "CONNECTION SUCCESS";
    }
    getAllProperties();
    return true;
}

//
// Init the two member vectors with all
// attribute's names and values
//
void Entity::getAllProperties()
{
    _propertiesName = new QVector<QString>;
    _propertiesValue = new QVector<QString>;

    const QMetaObject *metaObject = this->metaObject();
    int count = metaObject->propertyCount();
    int offset =  metaObject->propertyOffset();

    for (int i = offset; i < count; ++i) {
	QMetaProperty metaProperty = metaObject->property(i);
	const char *propertyName = metaProperty.name();
	_propertiesName->push_back(propertyName);

	QVariant value = property(propertyName);
	_propertiesValue->push_back(value.toString());
    }
}

//
// Send a query request to delete data
//
bool Entity::deleteQuery(AQueryBuilder *builder)
{
    QSqlRecord recQuery;

    if(!startConnection())
	return false;
    return (builder->build()->exec());
}

//
// Get a new fresh instance of the
// QueryBuilder, set with Entity data
//
AQueryBuilder *Entity::getQueryBuilder() const
{
    AQueryBuilder *ret = NULL;

    if (_dbType == MYSQL_TYPE)
	ret = new QueryBuilderMySql(_table, _db);
    else
	qDebug() << "Unknown database type";

    return (ret);
}
