#ifndef ENTITY_HPP_
# define ENTITY_HPP_

#include	<QSqlDatabase>
#include	<QObject>
#include	<QMetaObject>
#include	<QMetaProperty>
#include	<QStringList>
#include	<QVariant>
#include	<QString>

class Entity : public QObject
{
  Q_OBJECT

public:
  Entity();
  virtual ~Entity();

private:
  QSqlDatabase	*db;

protected:
  QString	table;

public:
  bool		connect();
  bool		save();
  QString	getTable() const;
  void		setTable(QString newTable);

};


#endif // !ENTITY_HPP_
