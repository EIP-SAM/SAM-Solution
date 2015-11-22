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


    // for (it = _bindedValues.begin(); it != _bindedValues.end(); ++it)
    // {
    // 	QVariant value(it.value());
    // 	_queryObj->bindValue(it.key(), value);
    // }

    return _queryObj;
}

const QString &AQueryBuilder::getQueryString() const
{
    return _queryStr;
}
