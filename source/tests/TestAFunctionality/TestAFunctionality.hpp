#ifndef TESTAFUNCTIONALITY_HPP
# define TESTAFUNCTIONALITY_HPP

# include "BasicAFunctionality.hpp"
# include <QTest>
# include <QObject>
# include <QSignalSpy>

class TestAFunctionality : public QObject {
	Q_OBJECT

public:
	TestAFunctionality();

	void TestStart();
	void TestStop();

signals:
	void start();
	void stop();

};

#endif // !TESTAFUNCTIONALITY_HPP