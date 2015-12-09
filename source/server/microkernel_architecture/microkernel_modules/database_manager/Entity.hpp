#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include "QueryBuilderMySql.hpp"
# include "QueryBuilderSqlite.hpp"

# include <QSqlDatabase>
# include <QObject>
# include <QMetaObject>
# include <QMetaProperty>
# include <QVariant>
# include <QString>
# include <QVector>
# include <QSqlRecord>
# include <QSqlQuery>
# include <QSqlError>

class Entity : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase *_db;
    QString _dbType;
    QVector<QString> *_propertiesName;
    QVector<QString> *_propertiesValue;
    bool connect();
    bool startConnection();
    void getAllProperties();
    QSqlQuery *prepareInsert() const;
    QSqlQuery *prepareUpdate() const;

protected:
    QString _table;
    const QString &getTable() const;
    void setTable(const QString &newTable);

public:
    Entity();
    virtual ~Entity();
    bool save();
    bool deleteQuery(AQueryBuilder *builder);
    AQueryBuilder *getQueryBuilder() const;


    //
    // Find and return the entity by its id
    // Function in .hpp because of templating
    //
    template<class T>
    T *find(int id)
    {
	if (!startConnection())
	    return NULL;

	AQueryBuilder *builder = getQueryBuilder();
	builder->select("*")
	    ->where("id = :id")
	    ->bindValue(":id", id)
	    ;

	QVector<T *> result = this->request<T>(builder);

	if (result.size() == 0)
	    return NULL;

	return result.at(0);
    }

    //
    // Send a query request and return the result
    // Function in .hpp because of templating
    //
    template<class T>
    QVector<T *> request(AQueryBuilder *builder)
    {
	QVector<T *> result;
	QSqlRecord recQuery;
	QSqlQuery *query;

	if (!startConnection())
	    return (result);
	query = builder->build();
	query->exec();
	while (query->next())
	{
	    recQuery = query->record();
	    T *entity = new T();
	    for (auto prop : _propertiesName->toStdVector())
	    {
		int index = recQuery.indexOf(prop);
		if (index < 0)
		    continue;
		entity->setProperty(prop.toLocal8Bit().constData(),
				    query->value(index));
	    }
	    result.push_back(entity);
	}
	return (result);
    }
};

#endif // !ENTITY_HPP_
