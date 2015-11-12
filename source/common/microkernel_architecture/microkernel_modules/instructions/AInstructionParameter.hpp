#ifndef AINSTRUCTION_PARAMETER_HPP_
# define AINSTRUCTION_PARAMETER_HPP_

class AInstruction;
class QByteArray;
struct instructionParameterHeader_t;

class AInstruction::Parameter
{
protected:
    AInstruction &_parent;
    instructionParameterHeader_t *_header = NULL;

public:
    Parameter(AInstruction &, instructionParameterHeader_t *);
    ~Parameter();

    void setHeader(instructionParameterHeader_t *);
    void setRawData(const QByteArray&);
    void appendRawData(const QByteArray&);
    void setType(unsigned int);
    void setSize(int);

    instructionParameterHeader_t *getHeader() const;
    bool isValid() const;
    QByteArray getRawData() const;
    unsigned int getType() const;
    int getSize() const;
};

#endif // !AINSTRUCTION_PARAMETER_HPP_
