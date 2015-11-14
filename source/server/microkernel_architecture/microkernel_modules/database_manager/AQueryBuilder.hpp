#ifndef QUERY_BUILDER_HPP_
# define QUERY_BUILDER_HPP_

# include <QSqlQuery>
# include <QSqlDatabase>
# include <QObject>
# include <QString>
# include <QVariant>

# include <map>

class AQueryBuilder : public QObject
{
    Q_OBJECT

public:
    AQueryBuilder(QString table, QSqlDatabase *db);
    virtual ~AQueryBuilder();

    virtual AQueryBuilder *deleteRow() = 0;
    virtual AQueryBuilder *select(QString str) = 0;
    virtual AQueryBuilder *join(QString table, QString firstOn, QString secondOn) = 0;
    virtual AQueryBuilder *leftJoin(QString table, QString firstOn, QString secondOn) = 0;
    virtual AQueryBuilder *rightJoin(QString table, QString firstOn, QString secondOn) = 0;
    virtual AQueryBuilder *where(QString str) = 0;
    virtual AQueryBuilder *andWhere(QString str) = 0;
    virtual AQueryBuilder *orWhere(QString str) = 0;
    virtual AQueryBuilder *orderBy(QString str) = 0;
    virtual AQueryBuilder *limit(QString str) = 0;
    virtual AQueryBuilder *limit(int nb) = 0;

    AQueryBuilder *bindValue(QString key, QString value);
    AQueryBuilder *bindValue(QString key, int value);

    QSqlQuery *build();

    QString getQueryString() const;

protected:
    QSqlQuery *_queryObj;
    QSqlDatabase *_db;
    QString _queryStr;
    QString _table;
    std::map<QString, QString> _bindedValues;

};

#endif // !QUERY_BUILDER_HPP_
