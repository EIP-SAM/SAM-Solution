#ifndef ENTITY_HPP_
# define ENTITY_HPP_

#include <QSqlDatabase>

class Entity
{
public:
  Entity();
  ~Entity();

private:
  QSqlDatabase *db;

public:
  bool Connect();
};


#endif // !ENTITY_HPP_
