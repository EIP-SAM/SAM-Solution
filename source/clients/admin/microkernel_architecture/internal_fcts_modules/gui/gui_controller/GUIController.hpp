#ifndef GUI_CONTROLLER_HPP_
# define GUI_CONTROLLER_HPP_

# include <QQmlApplicationEngine>

class GUIController : public QObject
{
    Q_OBJECT

private:
    QQmlApplicationEngine _qmlEngine;

public:
    explicit GUIController(QObject *parent = 0);
    ~GUIController();

    void init();

signals:

public slots:
};

#endif // !GUI_CONTROLLER_HPP_
