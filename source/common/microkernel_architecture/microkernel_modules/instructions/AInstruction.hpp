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
        unsigned int numberOfParameters;
    );

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
        unsigned int parameterSize;
        // byte_t parameterData[parameterSize];
    );

    //
    // The following values are often used during the creation of an
    // `AInstruction`, this is why they are stored staticaly
    //
    // They represent size and offsets of the previous defined
    // structure and their members
    //
    // Regarding `instructionHeader_t`
    static const std::size_t _INSTRUCTION_HEADER_SIZE;
    static const std::size_t _MAGIC_NUMBER_OFFSET;
    static const std::size_t _FIRST_TRANSMITTER_ID_OFFSET;
    static const std::size_t _FINAL_RECEIVER_ID_OFFSET;
    static const std::size_t _INSTRUCTION_CODE_OFFSET;
    static const std::size_t _RETURN_TYPE_OFFSET;
    static const std::size_t _NUMBER_OF_PARAMETERS_OFFSET;
    static const std::size_t _FIRST_PARAMETER_OFFSET;
    //
    // Regarding `instructionParameterHeader_t`
    static const std::size_t _INSTRUCTION_PARAMETER_HEADER_SIZE;
    static const std::size_t _PARAMETER_TYPE_OFFSET;
    static const std::size_t _PARAMETER_SIZE_OFFSET;
    static const std::size_t _PARAMETER_DATA_OFFSET;

protected:
    QByteArray _data;
    AInstructionBusClient *_localTransmitter = NULL;
    //
    // Pointers to data
    unsigned int *_magicNumber = NULL;
    AInstructionBusClient::eClientId *_firstTransmitterId = NULL;
    AInstructionBusClient::eClientId *_finalReceiverId = NULL;
    unsigned int *_instructionCode = NULL;
    unsigned int *_returnType = NULL;
    unsigned int *_numberOfParameters = NULL;
    void *_parametersData = NULL;

public:
    AInstruction();
    AInstruction(const AInstruction &);
    AInstruction(const QByteArray &);
    virtual ~AInstruction();

    void setRawData(const QByteArray &);
    void setLocalTransmitter(AInstructionBusClient *);
    void resetMagicNumber();
    void setFirstTransmitter(AInstructionBusClient::eClientId);
    void setFinalReceiver(AInstructionBusClient::eClientId);
    void setInstructionCode(unsigned int);
    void setReturnType(unsigned int);
    void setNumberOfParameters(unsigned int);
    void appendParameter(unsigned int, unsigned int, const void *);

    const QByteArray &getRawData() const;
    const AInstructionBusClient *getLocalTransmitter() const;
    bool isMagicNumberValid() const;
    AInstructionBusClient::eClientId getFirstTransmitter() const;
    AInstructionBusClient::eClientId getFinalReceiver() const;
    unsigned int getInstructionCode() const;
    unsigned int getReturnType() const;
    unsigned int getNumberOfParameters() const;
    unsigned int getParameterNumber(unsigned int, void *&) const;

protected:
    void _ensureMinimumDataSize(int minSize = _INSTRUCTION_HEADER_SIZE);
    void _setPointersToData();
};

#endif // !AINSTRUCTION_HPP_
