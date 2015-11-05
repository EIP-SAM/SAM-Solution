#include <QApplication>
#include <QDebug>
#include <QSqlQuery>
#include <vector>
#include <iostream>

#include "QueryBuilder.hpp"
#include "UsersEntity.hpp"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  UsersEntity user;

  user.setLogin("bernar_w");
  user.setPassword("PasswordQuiRox");

  if (user.save())
      qDebug() << "SAVE SUCCESS";
  else
      qDebug() << "SAVE FAIL";

  QueryBuilder *builder = user.getQueryBuilder();
  builder->select("id, login, password")
      ;

  std::vector<UsersEntity *> result = user.request<UsersEntity>(builder);

  for (std::vector<UsersEntity *>::iterator it = result.begin(); it != result.end(); ++it)
      std::cout << "Login : "<< (*it)->getLogin().toStdString() << std::endl;

  QueryBuilder *builder2 = user.getQueryBuilder();
  builder2->deleteRow()
      ->where("id = :id")
      ->bindValue(":id", 6)
      ;
  user.deleteQuery(builder2);

  return 0;
}
