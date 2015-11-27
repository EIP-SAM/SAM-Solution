#include "QueryBuilderMySql.hpp"

QueryBuilderMySql::QueryBuilderMySql(const QString &table, QSqlDatabase *db) : AQueryBuilder(table, db)
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
AQueryBuilder *QueryBuilderMySql::select(const QString &str)
{
    _queryStr += "SELECT " + str + " FROM " + _table;

    return (this);
}

//
// My SQL command 'join'
//
AQueryBuilder *QueryBuilderMySql::join(const QString &table, const QString &firstOn, const QString &secondOn)
{
    _queryStr += " JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'left join'
//
AQueryBuilder *QueryBuilderMySql::leftJoin(const QString &table, const QString &firstOn, const QString &secondOn)
{
    _queryStr += " LEFT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'right join'
//
AQueryBuilder *QueryBuilderMySql::rightJoin(const QString &table, const QString &firstOn, const QString &secondOn)
{
    _queryStr += " RIGHT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'where'
//
AQueryBuilder *QueryBuilderMySql::where(const QString &str)
{
    _queryStr += " WHERE " + str;

    return (this);
}

//
// My SQL command 'and'
//
AQueryBuilder *QueryBuilderMySql::andWhere(const QString &str)
{
    _queryStr += " AND " + str;

    return (this);
}

//
// My SQL command 'or'
//
AQueryBuilder *QueryBuilderMySql::orWhere(const QString &str)
{
    _queryStr += " OR " + str;

    return (this);
}

//
// My SQL command 'order by'
//
AQueryBuilder *QueryBuilderMySql::orderBy(const QString &str)
{
    _queryStr += " ORDER BY " + str;

    return (this);
}

//
// My SQL command 'limit'
//
AQueryBuilder *QueryBuilderMySql::limit(const QString &str)
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

//
//My SQL command 'update'
//
AQueryBuilder *QueryBuilderMySql::updateQuery(const QString &fields, const QString &whereClause)
{
    _queryStr += "UPDATE " + _table + " SET " +
	fields + " WHERE " + whereClause + ";";
    return (this);
}

//
//My SQL command 'insert'
//
AQueryBuilder *QueryBuilderMySql::insertQuery(const QString &fields, const QString &values)
{
    _queryStr += "INSERT INTO " + _table +
	" (" + fields + ") VALUES (" + values + ");";
    return (this);
}
