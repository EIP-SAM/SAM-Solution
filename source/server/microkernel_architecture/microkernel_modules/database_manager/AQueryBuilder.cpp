#include "AQueryBuilder.hpp"

AQueryBuilder::AQueryBuilder(QString table, QSqlDatabase *db)
{
    _queryObj = NULL;
    _table = table;
    _db = db;
}

AQueryBuilder::~AQueryBuilder()
{
}

AQueryBuilder *AQueryBuilder::bindValue(QString key, QString value)
{
    this->_bindedValues.insert(std::pair<QString,QString>(key, value));

    return (this);
}

AQueryBuilder *AQueryBuilder::bindValue(QString key, int value)
{
    this->_bindedValues.insert(std::pair<QString,QString>(key, QString::number(value)));

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

    this->_queryObj = new QSqlQuery(*(this->_db));
    this->_queryObj->prepare(this->_queryStr);

    for (it = this->_bindedValues.begin(); it != this->_bindedValues.end(); ++it)
    {
	QVariant value(it->second);
	this->_queryObj->bindValue(it->first, value);
    }

    return this->_queryObj;
}

QString AQueryBuilder::getQueryString() const
{
    return this->_queryStr;
}
