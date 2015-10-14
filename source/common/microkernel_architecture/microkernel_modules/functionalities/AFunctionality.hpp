#ifndef AFUNCTIONALITY_HPP_

# define AFUNCTIONALITY_HPP_

# include <QThread>

class FunctionalitiesManager;

class AFunctionality : public QThread
{  
  Q_OBJECT

public:
  AFunctionality();
  ~AFunctionality();
  
  void start(bool threaded = true, FunctionalitiesManager &manager);
  void stop();

signals:
  void starded(AFunctionalities *);

};

#endif // !AFUNCTIONALITY_HPP_
