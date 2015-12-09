#include "QueryBuilderSqlite.hpp"

QueryBuilderSqlite::QueryBuilderSqlite(const QString &table, QSqlDatabase *db) : AQueryBuilder(table, db)
{
}

QueryBuilderSqlite::~QueryBuilderSqlite()
{
}

//
// My SQL command 'delete'
//
AQueryBuilder *QueryBuilderSqlite::deleteRow()
{
    _queryStr += "DELETE FROM " + _table;

    return (this);
}

//
// My SQL command 'select'
//
AQueryBuilder *QueryBuilderSqlite::select(const QString &str)
{
    _queryStr += "SELECT " + str + " FROM " + _table;

    return (this);
}

//
// My SQL command 'join'
//
AQueryBuilder *QueryBuilderSqlite::join(const QString &table, const QString &firstOn, const QString &secondOn)
{
    _queryStr += " JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'left join'
//
AQueryBuilder *QueryBuilderSqlite::leftJoin(const QString &table, const QString &firstOn, const QString &secondOn)
{
    _queryStr += " LEFT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'right join'
//
AQueryBuilder *QueryBuilderSqlite::rightJoin(const QString &table, const QString &firstOn, const QString &secondOn)
{
    _queryStr += " RIGHT JOIN " + table + " on " + firstOn + " = " + secondOn;

    return (this);
}

//
// My SQL command 'where'
//
AQueryBuilder *QueryBuilderSqlite::where(const QString &str)
{
    _queryStr += " WHERE " + str;

    return (this);
}

//
// My SQL command 'and'
//
AQueryBuilder *QueryBuilderSqlite::andWhere(const QString &str)
{
    _queryStr += " AND " + str;

    return (this);
}

//
// My SQL command 'or'
//
AQueryBuilder *QueryBuilderSqlite::orWhere(const QString &str)
{
    _queryStr += " OR " + str;

    return (this);
}

//
// My SQL command 'order by'
//
AQueryBuilder *QueryBuilderSqlite::orderBy(const QString &str)
{
    _queryStr += " ORDER BY " + str;

    return (this);
}

//
// My SQL command 'limit'
//
AQueryBuilder *QueryBuilderSqlite::limit(const QString &str)
{
    _queryStr += " LIMIT " + str;

    return (this);
}

//
// My SQL command 'limit'
//
AQueryBuilder *QueryBuilderSqlite::limit(int nb)
{
    _queryStr += " LIMIT " + QString::number(nb);

    return (this);
}

//
//My SQL command 'update'
//
AQueryBuilder *QueryBuilderSqlite::updateQuery(const QString &fields, const QString &whereClause)
{
    _queryStr += "UPDATE " + _table + " SET " +
	fields + " WHERE " + whereClause + ";";
    return (this);
}

//
//My SQL command 'insert'
//
AQueryBuilder *QueryBuilderSqlite::insertQuery(const QString &fields, const QString &values)
{
    _queryStr += "INSERT INTO " + _table +
	" (" + fields + ") VALUES (" + values + ");";
    return (this);
}
