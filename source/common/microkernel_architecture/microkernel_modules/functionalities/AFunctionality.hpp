#ifndef AFUNCTIONALITY_HPP_
# define AFUNCTIONALITY_HPP_

# include <QThread>
# include "AInstructionBusClient.hpp"

//
// Note: Overload the run() method in child classes
// Then implement what the functionality is supposed to do
//

class AFunctionality : public AInstructionBusClient
{
    Q_OBJECT

private:
    QThread *_thread;
    bool _running;
    bool _threaded;

public:
    AFunctionality(QObject *parent = 0);
    virtual ~AFunctionality();

    bool start();
    void stop();
    void setThreaded(bool threaded);

    bool isThreaded() const;
    bool isRunning() const;

public slots:
    virtual void run() = 0;

private slots:
    void _fctStarted();
    void _fctFinished();

signals:
    void started();
    void stopped();
};

#endif // !AFUNCTIONALITY_HPP_
