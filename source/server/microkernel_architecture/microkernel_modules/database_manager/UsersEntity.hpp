#ifndef USERS_ENTITY_HPP_
# define USERS_ENTITY_HPP_

#include	"Entity.hpp"

class UsersEntity : public Entity
{

  Q_OBJECT

  Q_PROPERTY(int id READ getId WRITE setId)
  Q_PROPERTY(QString login READ getLogin WRITE setLogin)
  Q_PROPERTY(QString password READ getPassword WRITE setPassword)

public:
  UsersEntity();
  virtual ~UsersEntity();

protected:
  int		id;
  QString	login;
  QString	password;

public:
  int		getId() const;
  void		setId(int newId);
  QString	getLogin() const;
  void		setLogin(QString newLogin);
  QString	getPassword() const;
  void		setPassword(QString newPassword);

};


#endif // !USERS_ENTITY_HPP_
