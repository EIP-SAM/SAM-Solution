#ifndef     _QFILE_H
# define    _QFILE_H

# include   <QFile>

// `_QFile` is an extension of the original Qt class `QFile`

class _QFile : public QFile
{
public:
    explicit _QFile(QObject *parent = 0);

    static const QByteArray *readFile(const QString &filename);

signals:

public slots:
};

#endif      // _QFILE_H
