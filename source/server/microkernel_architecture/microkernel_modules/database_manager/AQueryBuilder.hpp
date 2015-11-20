#ifndef QUERY_BUILDER_HPP_
# define QUERY_BUILDER_HPP_

# include <QSqlQuery>
# include <QSqlDatabase>
# include <QObject>
# include <QString>
# include <QVariant>
# include <QMap>

class AQueryBuilder : public QObject
{
    Q_OBJECT

public:
    AQueryBuilder(const QString &table, QSqlDatabase *db);
    virtual ~AQueryBuilder();

    virtual AQueryBuilder *deleteRow() = 0;
    virtual AQueryBuilder *select(const QString &str) = 0;
    virtual AQueryBuilder *join(const QString &table, const QString &firstOn, const QString &secondOn) = 0;
    virtual AQueryBuilder *leftJoin(const QString &table, const QString &firstOn, const QString &secondOn) = 0;
    virtual AQueryBuilder *rightJoin(const QString &table, const QString &firstOn, const QString &secondOn) = 0;
    virtual AQueryBuilder *where(const QString &str) = 0;
    virtual AQueryBuilder *andWhere(const QString &str) = 0;
    virtual AQueryBuilder *orWhere(const QString &str) = 0;
    virtual AQueryBuilder *orderBy(const QString &str) = 0;
    virtual AQueryBuilder *limit(const QString &str) = 0;
    virtual AQueryBuilder *limit(int nb) = 0;

    virtual AQueryBuilder *updateQuery(const QString &fields, const QString &whereClause = "") = 0;
    virtual AQueryBuilder *insertQuery(const QString &fields, const QString &values = "") =0;

    AQueryBuilder *bindValue(const QString &key, const QString &value);
    AQueryBuilder *bindValue(const QString &key, int value);

    QSqlQuery *build();

    const QString &getQueryString() const;

protected:
    QSqlQuery *_queryObj;
    QSqlDatabase *_db;
    QString _queryStr;
    QString _table;
    QMap<QString, QString> _bindedValues;

};

#endif // !QUERY_BUILDER_HPP_
