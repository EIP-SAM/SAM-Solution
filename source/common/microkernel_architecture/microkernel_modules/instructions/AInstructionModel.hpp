#ifndef	AINSTRUCTION_MODEL_HPP_
# define AINSTRUCTION_MODEL_HPP_

# define CONTENT_BYTE_SIZE 10
# define INDEX_BYTE_INSTRUCTIONCODE 0
# define INDEX_BYTE_RETURNTYPE 4
# define INDEX_BYTE_ISSYNCHRONE 8

# include <QByteArray>

class AInstructionModel
{
public:
    AInstructionModel();
    ~AInstructionModel();

    void setByteArray(QByteArray *byteArray);
    QByteArray *getByteArray() const;

protected:
  QByteArray *_byteArray;
};

#endif // !AINSTRUCTION_MODEL_HPP_
