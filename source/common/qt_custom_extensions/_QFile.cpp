#include "_QFile.hpp"
#include <QDebug>

//
// Construct custom QFile
_QFile::_QFile(QObject *parent)
    : QFile(parent)
{
}

//
// Read a file and return its data
const QByteArray *_QFile::readFile(const QString &filename)
{
    QByteArray *data = NULL;
    QFile file(filename);

    if (!(data = new QByteArray))
        return (NULL);
    if (file.open(QIODevice::ReadOnly))
    {
        *data = file.readAll();
        file.close();
    }
    else
    {
        qDebug() << file.errorString();
        delete data;
        return (NULL);
    }
    return (data);
}
