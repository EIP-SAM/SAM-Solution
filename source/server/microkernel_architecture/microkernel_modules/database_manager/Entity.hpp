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
# include "QueryBuilderMySql.hpp"

# define MYSQL_TYPE "MYSQL"

class Entity : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase *_db;
    QString _dbType;
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
    bool deleteQuery(AQueryBuilder *builder);
    AQueryBuilder *getQueryBuilder();


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

      std::vector<T *> result = this->request<T>(builder);

      if (result.size() == 0)
	return NULL;

      return result.at(0);
    }

    //
    // Send a query request and return the result
    // Function in .hpp because of templating
    //
    template<class T>
    std::vector<T *> request(AQueryBuilder *builder)
	{
	    std::vector<T *> result;
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
