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

    bool _initFctsManager();
    
public:
    MainController(int, char **);
    ~MainController();
    
    int run();
	   
private slots:
    void _deleteFctsManager();
};

#endif // !MAIN_CONTROLLER_HPP_
