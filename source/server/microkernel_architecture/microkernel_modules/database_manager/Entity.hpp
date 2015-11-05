#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <QSqlDatabase>
# include <QObject>
# include <QMetaObject>
# include <QMetaProperty>
# include <QStringList>
# include <QVariant>
# include <QString>
# include <QSqlRecord>
# include <QSqlQuery>
# include "QueryBuilder.hpp"

class Entity : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase *_db;
    std::vector<QString> *_propertiesName;
    std::vector<QString> *_propertiesValue;
    bool connect();
    bool startConnection();
    void getAllProperties();
    QSqlQuery prepareInsert() const;
    QSqlQuery prepareUpdate() const;

protected:
    QString _table;
    QString getTable() const;
    void setTable(QString newTable);

public:
    Entity();
    virtual ~Entity();
    bool save();
    bool deleteQuery(QueryBuilder *builder);
    QueryBuilder *getQueryBuilder();

    //
    // Send a query request and return the result
    // Function in .hpp because of templating
    //
    template<class T>
    std::vector<T *> request(QueryBuilder *builder)
	{
	    std::vector<T *> result;
	    QSqlRecord recQuery;
	    QSqlQuery *query;

	    startConnection();
	    query = builder->build();
	    query->exec();
	    while (query->next())
	    {
		recQuery = query->record();
		T *entity = new T();
		for (std::vector<QString>::iterator it = _propertiesName->begin();
		     it != _propertiesName->end(); ++it)
		{
		    int index = recQuery.indexOf(*it);
		    if (index < 0)
			continue;
		    entity->setProperty((*it).toLocal8Bit().constData(),
					query->value(index));
		}
		result.push_back(entity);
	    }
	    return (result);
	}
};

#endif // !ENTITY_HPP_
