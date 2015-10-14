#ifndef FUNCTIONALITIES_MANAGER_HPP_
# define FUNCTIONALITIES_MANAGER_HPP_

# include <QList>
# include <QString>

# include "AFunctionality.hpp"

class FunctionalitiesManager
{
private:
  QList<AFunctionality *> _microkernelFcts;
  QList<AFunctionality *> _internalFcts;
  QList<AFunctionality *> _externalFcts;

public:
  FunctionalitiesManager();
  ~FunctionalitiesManager();

  void init();
  AFunctionality *loadLibrary(const QString &name);

private:
  void _initMicrokernelFcts();
  void _initInternalFcts();
  void _initExternalFcts();
};

#endif // !FUNCTIONALITIES_MANAGER_HPP_
