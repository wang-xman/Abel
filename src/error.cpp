#include "error.hpp"

namespace abel {

namespace error {

/* Base error class */
BaseError::BaseError() {}
BaseError::BaseError(const std::string& msg) : msg(msg) {}
BaseError::BaseError(const std::string&& msg) : msg(msg) {}
BaseError::~BaseError() {}

void BaseError::set_msg(std::string msg) { msg = msg; }
void BaseError::set_line(int line) { line_number = line; }

std::string BaseError::get_msg() { return msg; }
int BaseError::get_line() { return line_number; }
std::string BaseError::get_header() { return header; }

std::string BaseError::full_message()
{
    std::string full_string;
    if (get_line() < 0) {
        full_string = get_header() + "(" + get_msg() + ").";
    } else {
        full_string = get_header()
           + "(Line " + std::to_string( get_line() ) + ", "
           + get_msg() + ").";
    }
    return full_string;
}

void BaseError::make_show() { std::cout << full_message() << std::endl; }

/* Specialised error classes */

IncompatibleType::IncompatibleType() {}
IncompatibleType::IncompatibleType(const std::string& msg) : BaseError(msg) {}
IncompatibleType::IncompatibleType(const std::string&& msg) : BaseError(msg) {}
IncompatibleType::~IncompatibleType() {}
std::string IncompatibleType::get_header() { return header; }

IndexOutOfRange::IndexOutOfRange() {}
IndexOutOfRange::IndexOutOfRange(const std::string& msg) : BaseError(msg) {}
IndexOutOfRange::IndexOutOfRange(const std::string&& msg) : BaseError(msg) {}
IndexOutOfRange::~IndexOutOfRange() {}
std::string IndexOutOfRange::get_header() { return header; }

KeyNotFound::KeyNotFound() {}
KeyNotFound::KeyNotFound(const std::string& msg) : BaseError(msg) {}
KeyNotFound::KeyNotFound(const std::string&& msg) : BaseError(msg) {}
KeyNotFound::~KeyNotFound() {}
std::string KeyNotFound::get_header() { return header; }

DuplicateKey::DuplicateKey() {}
DuplicateKey::DuplicateKey(const std::string& msg) : BaseError(msg) {}
DuplicateKey::DuplicateKey(const std::string&& msg) : BaseError(msg) {}
DuplicateKey::~DuplicateKey() {}
std::string DuplicateKey::get_header() { return header; }

UnrecognizedSymbol::UnrecognizedSymbol() {}
UnrecognizedSymbol::UnrecognizedSymbol(const std::string& msg) : BaseError(msg) {}
UnrecognizedSymbol::UnrecognizedSymbol(const std::string&& msg) : BaseError(msg) {}
UnrecognizedSymbol::~UnrecognizedSymbol() {}
std::string UnrecognizedSymbol::get_header() { return header; }

TokenizationError::TokenizationError() {}
TokenizationError::TokenizationError(const std::string& msg) : BaseError(msg) {}
TokenizationError::TokenizationError(const std::string&& msg) : BaseError(msg) {}
TokenizationError::~TokenizationError() {}
std::string TokenizationError::get_header() { return header; }

SyntaxError::SyntaxError() {}
SyntaxError::SyntaxError(const std::string& msg) : BaseError(msg) {}
SyntaxError::SyntaxError(const std::string&& msg) : BaseError(msg) {}
SyntaxError::~SyntaxError() {}
std::string SyntaxError::get_header() { return header; }

UnpairedBrackets::UnpairedBrackets() {}
UnpairedBrackets::UnpairedBrackets(const std::string& msg) : BaseError(msg) {}
UnpairedBrackets::UnpairedBrackets(const std::string&& msg) : BaseError(msg) {}
UnpairedBrackets::~UnpairedBrackets() {}
std::string UnpairedBrackets::get_header() { return header; }

VariableNotFound::VariableNotFound() {}
VariableNotFound::VariableNotFound(const std::string& msg) : BaseError(msg) {}
VariableNotFound::VariableNotFound(const std::string&& msg) : BaseError(msg) {}
VariableNotFound::~VariableNotFound() {}
std::string VariableNotFound::get_header() { return header; }

InvalidInput::InvalidInput() {}
InvalidInput::InvalidInput(const std::string& msg) : BaseError(msg) {}
InvalidInput::InvalidInput(const std::string&& msg) : BaseError(msg) {}
InvalidInput::~InvalidInput() {}
std::string InvalidInput::get_header() { return header; }

DataTypeConversionError::DataTypeConversionError() {}
DataTypeConversionError::DataTypeConversionError(const std::string& msg) : BaseError(msg) {}
DataTypeConversionError::DataTypeConversionError(const std::string&& msg) : BaseError(msg) {}
DataTypeConversionError::~DataTypeConversionError() {}
std::string DataTypeConversionError::get_header() { return header; }

} // end error

}