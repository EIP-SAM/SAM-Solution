#ifndef MAIN_CONTROLLER_HPP_
# define MAIN_CONTROLLER_HPP_

# include "AMainController.hpp"
# include <QGuiApplication>

class MainController : public AMainController
{
    Q_OBJECT

private:
    QGuiApplication _qtCore;

public:
    MainController(int &, char **);
    virtual ~MainController();

    virtual int run();
};

# ifdef __MAIN_CONTROLLER_PRIVATE_DECL

MainController *mainController = NULL;

# else

extern MainController *mainController;

# endif // !__MAIN_CONTROLLER_PRIVATE_DECL

#endif // !MAIN_CONTROLLER_HPP_
