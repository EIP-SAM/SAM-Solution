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

  ////////////////////////////////////
  // Test the save() function
  ////////////////////////////////////
  user.setLogin("bernar_w2");
  user.setPassword("PasswordQuiRox");

  if (user.save())
      qDebug() << "SAVE SUCCESS";
  else
      qDebug() << "SAVE FAIL";

  ////////////////////////////////////
  // Test the request() function and
  // the QueryBuilder
  ////////////////////////////////////
  QueryBuilder *builder = user.getQueryBuilder();
  builder->select("id, login, password")
      ;

  std::vector<UsersEntity *> result = user.request<UsersEntity>(builder);

  for (std::vector<UsersEntity *>::iterator it = result.begin(); it != result.end(); ++it)
      std::cout << "Login : "<< (*it)->getLogin().toStdString() << std::endl;

  ////////////////////////////////////
  // Test the deleteQuery() function
  ////////////////////////////////////
  QueryBuilder *builder2 = user.getQueryBuilder();
  builder2->deleteRow()
      ->where("id = :id")
      ->bindValue(":id", 6)
      ;
  user.deleteQuery(builder2);

  ////////////////////////////////////
  // Test the find() function
  ////////////////////////////////////
  UsersEntity *found_user = user.find<UsersEntity>(1);

  if (found_user)
    std::cout << "Utilisateur trouvé : " << found_user->getLogin().toStdString() << std::endl;
  else
    std::cout << "Utilisateur non trouvé." << std::endl;

  return 0;
}
