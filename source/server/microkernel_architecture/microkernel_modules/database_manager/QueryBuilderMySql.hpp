#ifndef QUERY_BUILDER_MY_SQL_HPP_
# define QUERY_BUILDER_MY_SQL_HPP_

# include "AQueryBuilder.hpp"

class QueryBuilderMySql : public AQueryBuilder
{
    Q_OBJECT

public:
    QueryBuilderMySql(const QString &table, QSqlDatabase *db);
    virtual ~QueryBuilderMySql();

    virtual AQueryBuilder *deleteRow();
    virtual AQueryBuilder *select(const QString &str);
    virtual AQueryBuilder *join(const QString &table, const QString &firstOn, const QString &secondOn);
    virtual AQueryBuilder *leftJoin(const QString &table, const QString &firstOn, const QString &secondOn);
    virtual AQueryBuilder *rightJoin(const QString &table, const QString &firstOn, const QString &secondOn);
    virtual AQueryBuilder *where(const QString &str);
    virtual AQueryBuilder *andWhere(const QString &str);
    virtual AQueryBuilder *orWhere(const QString &str);
    virtual AQueryBuilder *orderBy(const QString &str);
    virtual AQueryBuilder *limit(const QString &str);
    virtual AQueryBuilder *limit(int nb);

    virtual AQueryBuilder *updateQuery(const QString &fields, const QString &whereClause = "");
    virtual AQueryBuilder *insertQuery(const QString &fields, const QString &values = "");
};

#endif // !QUERY_BUILDER_MYSQL_HPP_
