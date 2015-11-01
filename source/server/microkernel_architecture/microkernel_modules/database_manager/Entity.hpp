#ifndef ENTITY_HPP_
# define ENTITY_HPP_

#include	<QSqlDatabase>
#include	<QMetaObject>
#include	<string>

class Entity : public QMetaObject
{

public:
  Entity();
  ~Entity();

private:
  QSqlDatabase	*db;

protected:
  std::string	table;

public:
  bool		connect();
  bool		save();
  std::string	getTable() const;
  void		setTable(std::string newTable);

};


#endif // !ENTITY_HPP_
