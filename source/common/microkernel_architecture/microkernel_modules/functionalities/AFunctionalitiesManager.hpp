#ifndef AFUNCTIONALITIES_MANAGER_HPP_
# define AFUNCTIONALITIES_MANAGER_HPP_

# include <QList>
# include <QString>

# include "AFunctionality.hpp"

class AFunctionalitiesManager : public QObject
{
    Q_OBJECT

private:
    QList<AFunctionality *> _microkernelFcts;
    QList<AFunctionality *> _internalFcts;
    QList<AFunctionality *> _externalFcts;
    QList<AFunctionality *> _runningFcts;
    bool _shuttingDown;
    
    virtual void _setFcts() = 0;
    bool _initMicrokernelFcts();
    bool _initInternalFcts();
    bool _initExternalFcts();
    
public:
    AFunctionalitiesManager();
    virtual ~AFunctionalitiesManager();
    
    bool init();
    void shutdown();
    AFunctionality *loadLibrary(const QString &name);
						  
private slots:
    void _functionalityStarted();
    void _functionalityStopped();

signals:
    void readyToDelete();
};

#endif // !AFUNCTIONALITIES_MANAGER_HPP_
