#pragma once

class IpException {
public:
    enum class Exceptions {
        WrongArgsError,
        LoadFileError,
        WriteFileError,
        CmdParserError,
        InvalidFilterError,
        FileTypeError,
    };

    IpException(const Exceptions& exception_type) : exception_type_(exception_type) {};

    const Exceptions& GetExceptionType() const {
        return exception_type_;
    }

protected:
    Exceptions exception_type_;
};
