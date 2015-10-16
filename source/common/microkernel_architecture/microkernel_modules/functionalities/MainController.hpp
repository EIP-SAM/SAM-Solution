#ifndef MAIN_CONTROLLER_HPP_
# define MAIN_CONTROLLER_HPP_

# include <QCoreApplication>
# include "FunctionalitiesManager.hpp"

class MainController : QObject
{
  Q_OBJECT

private:
  QCoreApplication _qtCore;
  FunctionalitiesManager *_fctsManager;

public:
  MainController(int, char **);
  ~MainController();

  int run();

private:
  bool _initFctsManager();

private slots:
  void quit();
};

#endif // !MAIN_CONTROLLER_HPP_
