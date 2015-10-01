#include <QApplication>
#include <QQmlApplicationEngine>

#include "HelloWorld.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    HelloWorld::sayHello();

    return app.exec();
}
