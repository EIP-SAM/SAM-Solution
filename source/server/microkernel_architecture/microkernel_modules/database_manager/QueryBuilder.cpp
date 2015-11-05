#include "QueryBuilder.hpp"

QueryBuilder::QueryBuilder(QString table, QSqlDatabase *db)
{
    _queryObj = NULL;
    _table = table;
    _db = db;
}

QueryBuilder::~QueryBuilder()
{
}

QueryBuilder *QueryBuilder::deleteRow()
{
    this->_queryStr += "DELETE FROM " + this->_table;

    return (this);
}

QueryBuilder *QueryBuilder::select(QString str)
{
    this->_queryStr += "SELECT " + str + " FROM " + this->_table;

    return (this);
}

QueryBuilder *QueryBuilder::join(QString table, QString firstOn, QString secondOn)
{
    this->_queryStr += " JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

QueryBuilder *QueryBuilder::leftJoin(QString table, QString firstOn, QString secondOn)
{
    this->_queryStr += " LEFT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

QueryBuilder *QueryBuilder::rightJoin(QString table, QString firstOn, QString secondOn)
{
    this->_queryStr += " RIGHT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

QueryBuilder *QueryBuilder::where(QString str)
{
    this->_queryStr += " WHERE " + str;

    return (this);
}

QueryBuilder *QueryBuilder::addWhere(QString str)
{
    this->_queryStr += " AND " + str;

    return (this);
}

QueryBuilder *QueryBuilder::orWhere(QString str)
{
    this->_queryStr += " OR " + str;

    return (this);
}

QueryBuilder *QueryBuilder::orderBy(QString str)
{
    this->_queryStr += " ORDER BY " + str;

    return (this);
}

QueryBuilder *QueryBuilder::limit(QString str)
{
    this->_queryStr += " LIMIT " + str;

    return (this);
}

QueryBuilder *QueryBuilder::limit(int nb)
{
    this->_queryStr += " LIMIT " + QString::number(nb);

    return (this);
}

QueryBuilder *QueryBuilder::bindValue(QString key, QString value)
{
    this->_bindedValues.insert(std::pair<QString,QString>(key, value));

    return (this);
}

QueryBuilder *QueryBuilder::bindValue(QString key, int value)
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
QSqlQuery *QueryBuilder::build()
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

QString QueryBuilder::getQueryString() const
{
    return this->_queryStr;
}
