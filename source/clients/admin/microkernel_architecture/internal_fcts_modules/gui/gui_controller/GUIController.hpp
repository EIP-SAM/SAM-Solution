#ifndef GUI_CONTROLLER_HPP_
# define GUI_CONTROLLER_HPP_

# include <QQmlApplicationEngine>
# include "AFunctionality.hpp"

class GUIController : public AFunctionality
{
private:
    QQmlApplicationEngine _qmlEngine;

public:
    GUIController();
    virtual ~GUIController();

    void init();

signals:

public slots:
    virtual void run();
};

#endif // !GUI_CONTROLLER_HPP_
