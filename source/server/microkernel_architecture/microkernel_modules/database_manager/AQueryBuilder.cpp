#include "AQueryBuilder.hpp"

//
// Init attributs
//
AQueryBuilder::AQueryBuilder(const QString & table, QSqlDatabase *db) :  _queryObj(NULL), _db(db), _table(table)
{
}

AQueryBuilder::~AQueryBuilder()
{
}

//
// Bind value to construct a secure query
//
AQueryBuilder *AQueryBuilder::bindValue(const QString &key, const QString &value)
{
    _bindedValues.insert(key, value);
    return (this);
}

//
// Bind value to construct a secure query
//
AQueryBuilder *AQueryBuilder::bindValue(const QString &key, int value)
{
    _bindedValues.insert(key, QString::number(value));
    return (this);
}

//
// "Build" the QSqlQuery :
// - Prepare the query
// - Bind every saved value
// - Return the builded QSqlQuery
//
QSqlQuery *AQueryBuilder::build()
{
    QMap<QString, QString>::const_iterator it;

    _queryObj = new QSqlQuery(*(_db));
    _queryObj->prepare(_queryStr);

    for (auto key : _bindedValues.keys())
    {
	QVariant value(_bindedValues.value(key));
	_queryObj->bindValue(key, value);
    }

    return _queryObj;
}

const QString &AQueryBuilder::getQueryString() const
{
    return _queryStr;
}

QSqlDatabase *AQueryBuilder::connect(const std::string &dbType)
{
    QSqlDatabase *ret = new QSqlDatabase();
    *ret = QSqlDatabase::addDatabase(dbType.c_str());

    if (dbType == MYSQL_TYPE) {
	ret->setHostName("127.0.0.1");
	ret->setDatabaseName("test");
	ret->setUserName("root");
	ret->setPassword("root");
    } else if (dbType == SQLITE_TYPE) {
	ret->setDatabaseName("/opt/databases/sam.db");
    }
    else
	qDebug() << "Unknown database type";

    return (ret);
}
