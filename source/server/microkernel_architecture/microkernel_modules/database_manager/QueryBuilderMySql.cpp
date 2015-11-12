#include "QueryBuilderMySql.hpp"

QueryBuilderMySql::QueryBuilderMySql(QString table, QSqlDatabase *db) : AQueryBuilder(table, db)
{
}

QueryBuilderMySql::~QueryBuilderMySql()
{
}

AQueryBuilder *QueryBuilderMySql::deleteRow()
{
    this->_queryStr += "DELETE FROM " + this->_table;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::select(QString str)
{
    this->_queryStr += "SELECT " + str + " FROM " + this->_table;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::join(QString table, QString firstOn, QString secondOn)
{
    this->_queryStr += " JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::leftJoin(QString table, QString firstOn, QString secondOn)
{
    this->_queryStr += " LEFT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::rightJoin(QString table, QString firstOn, QString secondOn)
{
    this->_queryStr += " RIGHT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::where(QString str)
{
    this->_queryStr += " WHERE " + str;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::addWhere(QString str)
{
    this->_queryStr += " AND " + str;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::orWhere(QString str)
{
    this->_queryStr += " OR " + str;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::orderBy(QString str)
{
    this->_queryStr += " ORDER BY " + str;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::limit(QString str)
{
    this->_queryStr += " LIMIT " + str;

    return (this);
}

AQueryBuilder *QueryBuilderMySql::limit(int nb)
{
    this->_queryStr += " LIMIT " + QString::number(nb);

    return (this);
}
