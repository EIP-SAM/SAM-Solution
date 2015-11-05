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

class Entity : public QObject
{
    Q_OBJECT

private:
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
    QSqlDatabase *_db;
    Entity();
    virtual ~Entity();
    bool save();
    bool deleteQuery(QSqlQuery *query);

    //
    // Send a query request and return the result
    // Function in .hpp because of templating
    //
    template<class T>
    std::vector<T *> request(QSqlQuery *query)
	{
	    std::vector<T *> result;
	    QSqlRecord recQuery;

	    startConnection();
	    query->exec();
	    recQuery = query->record();
	    while (query->next())
	    {
		T *entity = new T();
		for (std::vector<QString>::iterator it = _propertiesName->begin();
		     it != _propertiesName->end(); ++it)
		{
		    int index = recQuery.indexOf(*it);
		    qDebug() << entity->setProperty((*it).toLocal8Bit().constData(), query->value(index));
		    qDebug() << (*it).toLocal8Bit().constData() << " ==> " << query->value(index);
		}
		result.push_back(entity);
	    }
	    return (result);
	}
};

#endif // !ENTITY_HPP_
