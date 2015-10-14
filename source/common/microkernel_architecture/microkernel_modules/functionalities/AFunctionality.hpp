#ifndef AFUNCTIONALITY_HPP_

# define AFUNCTIONALITY_HPP_

# include <QThread>

class AFunctionality : public QThread
{  
  Q_OBJECT

public:
  AFunctionality();
  ~AFunctionality();
  
  void start(bool threaded = true);
  void stop();

signals:
  void starded();

};

#endif // !AFUNCTIONALITY_HPP_
