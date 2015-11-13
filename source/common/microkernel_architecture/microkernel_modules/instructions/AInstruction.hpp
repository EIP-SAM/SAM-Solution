#ifndef AINSTRUCTION_HPP_
# define AINSTRUCTION_HPP_

# include "AInstructionBusClient.hpp"
# include "struct_packed.h"
# include <QByteArray>

typedef unsigned int magicNumber_t;

class AInstruction
{
private:
    static const magicNumber_t _MAGIC_NUMBER;

protected:
    //
    // `struct instructionHeader_t` represents how the data is
    // supposed to be organized inside `QByteArray _data`
    // It should represent the first bytes of `_data`
    //
    // These bytes will be followed by the data representing the
    // parameters, if `numberOfParameters` > 0
    // Note: The parameters data representation is described below
    //
    STRUCT_PACKED(instructionHeader_t,
        magicNumber_t magicNumber;
        AInstructionBusClient::eClientId firstTransmitterId;
        AInstructionBusClient::eClientId finalReceiverId;
        unsigned int instructionCode;
        unsigned int returnType;
        int numberOfParameters;
    );
    struct instructionHeader_t;

    //
    // `struct instructionParameterHeader_t` represents how the data
    // is supposed to be organized inside `QByteArray _data`, after
    // the bytes representing the instruction header
    //
    // The first two parameters will be followed by
    // `parameterSize` bytes, these are the parameter data
    //
    // The next parameter, if any, is directly after the last
    // parameter byte, symbolized by `parameterData[parameterSize]`
    //
    STRUCT_PACKED(instructionParameterHeader_t,
        unsigned int parameterType;
        int parameterSize;
        // byte_t parameterData[parameterSize];
    );
    struct instructionParameterHeader_t;

    //
    // The following values are often used during the creation
    // or during the reading/filling of an `AInstruction`
    //
    // Regarding `instructionHeader_t`
    static const int _INSTRUCTION_HEADER_SIZE;
    static const int _FIRST_PARAMETER_OFFSET;
    //
    // Regarding `instructionParameterHeader_t`
    static const int _INSTRUCTION_PARAMETER_HEADER_SIZE;
    static const int _PARAMETER_DATA_OFFSET;

public:
    class Parameter;

protected:
    QByteArray _data;
    AInstructionBusClient *_localTransmitter = NULL;
    instructionHeader_t *_header = NULL;
    QList<Parameter *> _parameters;

public:
    AInstruction();
    AInstruction(const AInstruction &);
protected:
    AInstruction(const QByteArray&);
public:
    virtual ~AInstruction();

    void setLocalTransmitter(AInstructionBusClient *);
    void resetMagicNumber();
    void setFirstTransmitter(AInstructionBusClient::eClientId);
    void setFinalReceiver(AInstructionBusClient::eClientId);
    void setInstructionCode(unsigned int);
    void setReturnType(unsigned int);
    Parameter *createParameter(int size = 0);
    void deleteParameterNumber(int);

    const AInstructionBusClient *getLocalTransmitter() const;
    bool isMagicNumberValid() const;
    AInstructionBusClient::eClientId getFirstTransmitter() const;
    AInstructionBusClient::eClientId getFinalReceiver() const;
    unsigned int getInstructionCode() const;
    unsigned int getReturnType() const;
    int getNumberOfParameters() const;
    Parameter *getParameterNumber(int) const;

protected:
    instructionParameterHeader_t *_getParameterNumber(int) const;
    void _ensureMinimumDataSize(int minSize = _INSTRUCTION_HEADER_SIZE);
    void _setPointerToData();
    bool _parameterIsValid(instructionParameterHeader_t *);
    void _resizeParameter(instructionParameterHeader_t *, int);
    void _resetPointersToParameters();
};

# include "AInstructionParameter.hpp"

#endif // !AINSTRUCTION_HPP_
