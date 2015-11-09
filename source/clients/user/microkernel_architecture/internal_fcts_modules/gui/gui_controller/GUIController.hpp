#ifndef GUI_CONTROLLER_HPP_
# define GUI_CONTROLLER_HPP_

# include <QQmlApplicationEngine>
# include "AFunctionality.hpp"

class GUIController : public AFunctionality
{
    Q_OBJECT

private:
    QQmlApplicationEngine _qmlEngine;

public:
    GUIController();
    virtual ~GUIController();

    void init();

public slots:
    virtual void run();
};

#endif // !GUI_CONTROLLER_HPP_
