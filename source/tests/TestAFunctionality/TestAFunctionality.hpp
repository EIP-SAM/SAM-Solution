#ifndef TESTAFUNCTIONALITY_HPP
# define TESTAFUNCTIONALITY_HPP

# include <QTest>
# include <QObject>
# include <QSignalSpy>
# include "BasicAFunctionality.hpp"

class TestAFunctionality : public QObject {
    Q_OBJECT
    
public:
    TestAFunctionality();
			
private slots:
    void testStart();
    void testStop();
};

#endif // !TESTAFUNCTIONALITY_HPP
