#ifndef FOOBARINSTRUCTION_HPP_
# define FOOBARINSTRUCTION_HPP_

# include "AInstruction.hpp"
# include <QString>

class FooBarInstruction : public AInstruction
{
private:
    Parameter *_foo = NULL;
    Parameter *_bar = NULL;

public:
    FooBarInstruction();
    ~FooBarInstruction();

    bool init(int foo, const QString& bar);
    void setFoo(int);
    void setBar(const QString &);

    int getFoo() const;
    QString getBar() const;
};

#endif // !FOOBARINSTRUCTION_HPP_
