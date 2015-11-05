#ifndef QUERYBUILDER_HPP_
# define QUERYBUILDER_HPP_

# include <QSqlQuery>
# include <QSqlDatabase>
# include <QObject>
# include <QString>
# include <QVariant>

# include <map>

class QueryBuilder : public QObject
{
    Q_OBJECT

public:
    QueryBuilder(QString table, QSqlDatabase *db);
    virtual ~QueryBuilder();

    QueryBuilder *deleteRow();
    QueryBuilder *select(QString str);
    QueryBuilder *join(QString table, QString firstOn, QString secondOn);
    QueryBuilder *leftJoin(QString table, QString firstOn, QString secondOn);
    QueryBuilder *rightJoin(QString table, QString firstOn, QString secondOn);
    QueryBuilder *where(QString str);
    QueryBuilder *addWhere(QString str);
    QueryBuilder *orWhere(QString str);
    QueryBuilder *orderBy(QString str);
    QueryBuilder *limit(QString str);
    QueryBuilder *limit(int nb);

    QueryBuilder *bindValue(QString key, QString value);
    QueryBuilder *bindValue(QString key, int value);

    QSqlQuery *build();

    QString getQueryString() const;

private:
    QSqlQuery *_queryObj;
    QSqlDatabase *_db;
    QString _queryStr;
    QString _table;
    std::map<QString, QString> _bindedValues;

};

#endif // !QUERYBUILDER_HPP_
