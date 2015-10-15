#ifndef AFUNCTIONALITY_HPP_
# define AFUNCTIONALITY_HPP_

# include <QThread>

class AFunctionality : public QObject
{  
  Q_OBJECT

private:
  QThread *_thread;
  bool _running;

public:
  AFunctionality();
  virtual ~AFunctionality();
  
  void start(bool threaded = true);
  void stop();

private slots:
  void _fctStarted();
  void _fctFinished();

signals:
  void started();
  void stopped();
};

#endif // !AFUNCTIONALITY_HPP_
