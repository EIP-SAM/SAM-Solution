#include "AQueryBuilder.hpp"

//
// Init attributs
//
AQueryBuilder::AQueryBuilder(QString table, QSqlDatabase *db)
{
    _queryObj = NULL;
    _table = table;
    _db = db;
}

AQueryBuilder::~AQueryBuilder()
{
}

//
// Bind value to construct a secure query
//
AQueryBuilder *AQueryBuilder::bindValue(QString key, QString value)
{
    _bindedValues.insert(std::pair<QString,QString>(key, value));
    return (this);
}

//
// Bind value to construct a secure query
//
AQueryBuilder *AQueryBuilder::bindValue(QString key, int value)
{
    _bindedValues.insert(std::pair<QString,QString>(key, QString::number(value)));
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
    std::map<QString, QString>::const_iterator it;

    _queryObj = new QSqlQuery(*(_db));
    _queryObj->prepare(_queryStr);

    for (it = _bindedValues.begin(); it != _bindedValues.end(); ++it)
    {
	QVariant value(it->second);
	_queryObj->bindValue(it->first, value);
    }

    return _queryObj;
}

QString AQueryBuilder::getQueryString() const
{
    return _queryStr;
}
