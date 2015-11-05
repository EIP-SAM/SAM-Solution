#include <QApplication>
#include "UsersEntity.hpp"
#include <QDebug>
#include <QSqlQuery>
#include <vector>
#include "Entity.hpp"
#include <iostream>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  UsersEntity user;

  user.setId(2);
  user.setLogin("bernar_w");
  user.setPassword("PasswordQuiRox");

  if (user.save())
      qDebug() << "SAVE SUCCESS";
  else
      qDebug() << "SAVE FAIL";

  QSqlQuery *query = new QSqlQuery(*user._db);
  query->prepare("SELECT * FROM Users WHERE login LIKE :value");
  query->bindValue(":value", "bernar_w");
  std::vector<UsersEntity *> result = user.request<UsersEntity>(query);

  for (std::vector<UsersEntity *>::iterator it = result.begin(); it != result.end(); ++it)
      qDebug() << (*it)->getLogin();

  QSqlQuery *query2 = new QSqlQuery(*user._db);
  query2->prepare("DELETE FROM Users WHERE login LIKE :value");
  query2->bindValue(":value", "bernar_w");
  qDebug() << user.deleteQuery(query2);

  std::vector<UsersEntity *> result2 = user.request<UsersEntity>(query);
  for (std::vector<UsersEntity *>::iterator it = result2.begin(); it != result2.end(); ++it)
      qDebug() << (*it)->getLogin();
  return 0;
}
