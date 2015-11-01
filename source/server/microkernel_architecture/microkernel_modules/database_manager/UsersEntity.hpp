#ifndef USERS_ENTITY_HPP_
# define USERS_ENTITY_HPP_

#include	"Entity.hpp"

class UsersEntity : public Entity
{

public:
  UsersEntity();
  ~UsersEntity();

protected:
  int		id;
  std::string	login;
  std::string	password;

public:
  int		getId() const;
  void		setId(int newId);
  std::string	getLogin() const;
  void		setLogin(std::string newLogin);
  std::string	getPassword() const;
  void		setPassword(std::string newPassword);

};


#endif // !USERS_ENTITY_HPP_
