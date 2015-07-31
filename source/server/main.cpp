#include <QCoreApplication>

//#include <QDebug>
#include "HelloWorld.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Server: Hello world!";
    HelloWorld::sayHello();

    return a.exec();
}
