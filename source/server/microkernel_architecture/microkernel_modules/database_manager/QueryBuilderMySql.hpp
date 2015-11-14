#ifndef QUERY_BUILDER_MY_SQL_HPP_
# define QUERY_BUILDER_MY_SQL_HPP_

# include "AQueryBuilder.hpp"

class QueryBuilderMySql : public AQueryBuilder
{
    Q_OBJECT

public:
    QueryBuilderMySql(QString table, QSqlDatabase *db);
    virtual ~QueryBuilderMySql();

    virtual AQueryBuilder *deleteRow();
    virtual AQueryBuilder *select(QString str);
    virtual AQueryBuilder *join(QString table, QString firstOn, QString secondOn);
    virtual AQueryBuilder *leftJoin(QString table, QString firstOn, QString secondOn);
    virtual AQueryBuilder *rightJoin(QString table, QString firstOn, QString secondOn);
    virtual AQueryBuilder *where(QString str);
    virtual AQueryBuilder *andWhere(QString str);
    virtual AQueryBuilder *orWhere(QString str);
    virtual AQueryBuilder *orderBy(QString str);
    virtual AQueryBuilder *limit(QString str);
    virtual AQueryBuilder *limit(int nb);
};

#endif // !QUERY_BUILDER_MYSQL_HPP_
