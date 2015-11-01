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
  bool _shuttingDown;

public:
  FunctionalitiesManager();
  ~FunctionalitiesManager();

  bool init();
  void shutdown();
  AFunctionality *loadLibrary(const QString &name);

private:
  bool _initMicrokernelFcts();
  bool _initInternalFcts();
  bool _initExternalFcts();

private slots:
  void _functionalityStarted();
  void _functionalityStopped();

signals:
  void quit();
  void readyToDelete();
};

#endif // !FUNCTIONALITIES_MANAGER_HPP_
