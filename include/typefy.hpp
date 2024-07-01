#ifndef ABEL_TYPEFY_HPP
#define ABEL_TYPEFY_HPP

#include <string>
#include <vector>
#include <complex>
#include <memory>
#include <map>
#include <algorithm>
#include <type_traits>

namespace abel {

namespace cnt {}

namespace symbol {}

namespace util {}

namespace converter {}

class object;

class Null;

class Bool;

class Text;

template <typename> class numeric;

class Integer;

class Double;

template <typename> class complex;

class Complex;

class Binary;

class Bitstring;

class List;

class Tuple;

class Dict;

struct DataTypeIdentifier;

struct DelimiterPair;

class DelimiterMatch;

template<typename T> struct Token;

struct JsonToken;

template <typename T> class parser;

template <typename T, typename U, typename V> class container_parser; 

class JsonParser;

class JsonPlusParser;

template <typename T, typename U> class container_loader;

class JsonLoader;

class JsonPlusLoader;

}
#endif