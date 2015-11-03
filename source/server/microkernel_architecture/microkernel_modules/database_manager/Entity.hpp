#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <QSqlDatabase>
# include <QObject>
# include <QMetaObject>
# include <QMetaProperty>
# include <QStringList>
# include <QVariant>
# include <QString>

class Entity : public QObject
{
    Q_OBJECT

public:
    Entity();
    virtual ~Entity();

private:
    QSqlDatabase *_db;
    std::vector<QString> *_propertiesName;
    std::vector<QString> *_propertiesValue;

protected:
    QString _table;

private:
    bool connect();
    bool startConnection();
    void getAllProperties();
    QSqlQuery prepareInsert() const;
    QSqlQuery prepareUpdate() const;
    QString getTable() const;
    void setTable(QString newTable);

public:
    bool save();
    std::vector<Entity *> where(QString field, QString comparator, QString value);
    // std::vector<Entity *> where(QString field, QString comparator, std::vector<QString> values);
    // std::vector<Entity *> where(std::vector<QString>, std::vector<QString> comparator,
    // 				std::vector<std::vector<QString> >);
};

#endif // !ENTITY_HPP_
