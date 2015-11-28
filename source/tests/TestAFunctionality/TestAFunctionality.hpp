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

private slots:
    void testStart();
    void testStop();
};

#endif // !TESTAFUNCTIONALITY_HPP
