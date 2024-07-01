#ifndef ABEL_ERROR_HPP
#define ABEL_ERROR_HPP

#include <exception>
#include <iostream>
#include <string>

namespace abel {

namespace error {

/* Base error class */
class BaseError : public std::exception {
protected:
    std::string header = "BaseError";
    std::string msg    = "";
    int line_number    = -9999;
public:
    BaseError();
    explicit BaseError(const std::string&);
    explicit BaseError(const std::string&&);
    virtual ~BaseError();

    virtual void set_msg(std::string);
    virtual void set_line(int);

    virtual std::string get_msg(); // message body
    virtual int get_line();
    virtual std::string get_header();
    virtual std::string full_message();
    virtual void make_show(); // show full message
};

/* Specialised error classes */

class IncompatibleType : public BaseError {
protected:
    std::string header = "INCOMPATIBLE_TYPE";
public:
    IncompatibleType();
    explicit IncompatibleType(const std::string&);
    explicit IncompatibleType(const std::string&&);
    ~IncompatibleType();
    std::string get_header();
};

class IndexOutOfRange : public BaseError {
protected:
    std::string header = "INDEX_OUT_OF_RANGE";
public:
    IndexOutOfRange();
    explicit IndexOutOfRange(const std::string&);
    explicit IndexOutOfRange(const std::string&&);
    ~IndexOutOfRange();
    std::string get_header();
};

class KeyNotFound : public BaseError {
protected:
    std::string header = "KEY_NOT_FOUND";
public:
    KeyNotFound();
    explicit KeyNotFound(const std::string&);
    explicit KeyNotFound(const std::string&&);
    ~KeyNotFound();
    std::string get_header();
};

class DuplicateKey : public BaseError {
protected:
    std::string header = "DUPLICATE_KEY";
public:
    DuplicateKey();
    explicit DuplicateKey(const std::string&);
    explicit DuplicateKey(const std::string&&);
    ~DuplicateKey();
    std::string get_header();
};

class UnrecognizedSymbol : public BaseError {
protected:
    std::string header {"UNRECOGNIZED_SYMBOL"};
public:
    UnrecognizedSymbol();
    explicit UnrecognizedSymbol(const std::string&);
    explicit UnrecognizedSymbol(const std::string&&);
    ~UnrecognizedSymbol();
    std::string get_header();
};

class TokenizationError : public BaseError {
protected:
    std::string header = "TOKENIZATION_ERROR";
public:
    TokenizationError();
    explicit TokenizationError(const std::string&);
    explicit TokenizationError(const std::string&&);
    ~TokenizationError();
    std::string get_header();
};

class SyntaxError : public BaseError {
protected:
    std::string header = "SYNTAX_ERROR";
public:
    SyntaxError();
    explicit SyntaxError(const std::string&);
    explicit SyntaxError(const std::string&&);
    ~SyntaxError();
    std::string get_header();
};

class UnpairedBrackets : public BaseError {
protected:
    std::string header = "UNPAIRED_BRACKETS";
public:
    UnpairedBrackets();
    explicit UnpairedBrackets(const std::string&);
    explicit UnpairedBrackets(const std::string&&);
    ~UnpairedBrackets();
    std::string get_header();
};

class VariableNotFound : public BaseError {
protected:
    std::string header = "VARIABLE_NOT_FOUND";
public:
    VariableNotFound();
    explicit VariableNotFound(const std::string&);
    explicit VariableNotFound(const std::string&&);
    ~VariableNotFound();
    std::string get_header();
};

class InvalidInput : public BaseError {
protected:
    std::string header = "INVALID_INPUT";
public:
    InvalidInput();
    explicit InvalidInput(const std::string&);
    explicit InvalidInput(const std::string&&);
    ~InvalidInput();
    std::string get_header();
};

class DataTypeConversionError : public BaseError {
protected:
    std::string header = "DATA_TYPE_CONVERSION_ERROR";
public:
    DataTypeConversionError();
    explicit DataTypeConversionError(const std::string&);
    explicit DataTypeConversionError(const std::string&&);
    ~DataTypeConversionError();
    std::string get_header();
};

} // end error

}
#endif