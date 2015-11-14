#include "QueryBuilderMySql.hpp"

QueryBuilderMySql::QueryBuilderMySql(QString table, QSqlDatabase *db) : AQueryBuilder(table, db)
{
}

QueryBuilderMySql::~QueryBuilderMySql()
{
}

//
// My SQL command 'delete'
//
AQueryBuilder *QueryBuilderMySql::deleteRow()
{
    _queryStr += "DELETE FROM " + _table;

    return (this);
}

//
// My SQL command 'select'
//
AQueryBuilder *QueryBuilderMySql::select(QString str)
{
    _queryStr += "SELECT " + str + " FROM " + _table;

    return (this);
}

//
// My SQL command 'join'
//
AQueryBuilder *QueryBuilderMySql::join(QString table, QString firstOn, QString secondOn)
{
    _queryStr += " JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'left join'
//
AQueryBuilder *QueryBuilderMySql::leftJoin(QString table, QString firstOn, QString secondOn)
{
    _queryStr += " LEFT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'right join'
//
AQueryBuilder *QueryBuilderMySql::rightJoin(QString table, QString firstOn, QString secondOn)
{
    _queryStr += " RIGHT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'where'
//
AQueryBuilder *QueryBuilderMySql::where(QString str)
{
    _queryStr += " WHERE " + str;

    return (this);
}

//
// My SQL command 'and'
//
AQueryBuilder *QueryBuilderMySql::andWhere(QString str)
{
    _queryStr += " AND " + str;

    return (this);
}

//
// My SQL command 'or'
//
AQueryBuilder *QueryBuilderMySql::orWhere(QString str)
{
    _queryStr += " OR " + str;

    return (this);
}

//
// My SQL command 'order by'
//
AQueryBuilder *QueryBuilderMySql::orderBy(QString str)
{
    _queryStr += " ORDER BY " + str;

    return (this);
}

//
// My SQL command 'limit'
//
AQueryBuilder *QueryBuilderMySql::limit(QString str)
{
    _queryStr += " LIMIT " + str;

    return (this);
}

//
// My SQL command 'limit'
//
AQueryBuilder *QueryBuilderMySql::limit(int nb)
{
    _queryStr += " LIMIT " + QString::number(nb);

    return (this);
}
