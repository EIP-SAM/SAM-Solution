#ifndef GUI_CONTROLLER_HPP_
# define GUI_CONTROLLER_HPP_

# include <QQmlApplicationEngine>
# include "AFunctionality.hpp"

class GUIController : public AFunctionality
{
private:
    QQmlApplicationEngine _qmlEngine;

public:
    explicit GUIController(QObject *parent = 0);
    virtual ~GUIController();

    void init();

signals:

public slots:
};

#endif // !GUI_CONTROLLER_HPP_
