#ifndef FUNCTIONALITIES_MANAGER_HPP_
# define FUNCTIONALITIES_MANAGER_HPP_

# include <QList>
# include <QString>

# include "AFunctionality.hpp"

class FunctionalitiesManager : public QObject
{
  Q_OBJECT

private:
  QList<AFunctionality *> _microkernelFcts;
  QList<AFunctionality *> _internalFcts;
  QList<AFunctionality *> _externalFcts;
  QList<AFunctionality *> _runningFcts;

public:
  FunctionalitiesManager();
  ~FunctionalitiesManager();

  void init();
  void shutdown();
  AFunctionality *loadLibrary(const QString &name);

private:
  void _initMicrokernelFcts();
  void _initInternalFcts();
  void _initExternalFcts();

private slots:
  void _functionalityStarted();
  void _functionalityStopped();
};

#endif // !FUNCTIONALITIES_MANAGER_HPP_
