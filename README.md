# Abel - Containers, JSON Parsers, and Beyond

In a short summary, part of the Abel library is designed to supply Python-like dictionary and list containers that are capable of storing
*any legitimate type* of data. Well, the definition of *any legitimate type* is explained later. Besides a root class
based on which user-defined types can be introduced, Abel also provides
prefabed *intrinsic types* that are available to model most data. Before I bore you with its design which you can easily find out yourself, I shall
quickly switch to more practical and perhaps more interesting matters. 

An immediate use case of Abel is parsing a `JSON`-formatted file and loading
it as an (Abel) container. The standard datatypes that `JSON` accepts, i.e.
`Null`, `Bool`, `Double`, and string are part of Abel instrinsic types.

Beyond `JSON`, Abel introduces a more relaxed `JSON`-based format, coined as
`JSON+` (JSON plus). `JSON+` format accepts comments and is capable of parsing
and storing more datatypes.

## Abel intrinsic types

Current version of Abel supplies the following datatypes as its
*Abel intrinsic types*, or simply *intrinsics*. Most intrinsics are directly convertable to its conjugate C++ primitive (listed in the bracket).

- Null `abel::Null`

  Note. Type `abel::Null` exists only to accept the `null` used in JSON.
  It must be distinguished from the C++ `Null` pointer. 

- Bool `abel::Bool` (`bool`)

- Integer `abel::Integer` (`int`)

- Double `abel::Double` (`double`)

- Complex `abel::Complex` (`complex`)
  
  Abel provides a class template `complex<T>` and a specialised type
  `Complex` that is `complex<double>`.

- Text `abel::Text` (`std::string`)

  The most natural name for this type should be `String`. Due to the
  unfortunate name clash in the Abel library coded in another programming
  language, I had to choose this `Text`.

- Binary `abel::Binary`

- Bitstring `abel::Bitstring`

## Abel container types

Current version provides two primary containers and they are designed to store
any legitimate type, i.e. Abel intrinsic types, Abel container types, and any
type that is derived from Abel root class.

- Dictionary `abel::Dict`

  Dictionary stores a key-value pair. The key must be a `std::string` and
  the value can be any legitimate type.

- List `abel::List`

  A vector-like container that accepts any legitimate type as its element.

## Standard `JSON` parser

Abel library provides a parser class `abel::JsonParser` to parse a `JSON`-
formatted file, and a *loader* class `abel::JsonLoader` to load (from the
parser) the parsed content into a Abel dictionary. You are strongly encouraged
to walk through the examples provided in the directory `examples`. The comments
there are a bit verbose, but they explain in details the following essential
steps, namely, *parsing*, *loading*, and *getting*.

### Parsing a file

Given an `input_file_stream`, the parsing process requires 2 lines

```
abel::JsonParser json_parser;
json_parser.parse(input_file_stream);
```        

### Loading the content

And, loading from the parser is also simple: Define an Abel dictionary and
load the parsed content into it

```
std::shared_ptr<abel::Dict> global_dictionary ( new abel::Dict() );
abel::JsonLoader json_loader;
json_loader.load_from_parser(json_parser, global_dictionary);
```

The `global_dictionary` shall look like this
```
{
    "ROOT_KEY_" : [
        content_of_the_file
    ]
}
```
This dictionary has a key `"ROOT_KEY_"` and its value is a `abel::List`. You
shall find the content of the JSON file, be it a dictionary or a list, as an
element of this list.

### Getting the target

Abel provides a powerful and recommended method
```
abel::cnt::get<T>([source], [target])
```
to facilitate data access from containers. Simply speaking,

- template parameter `T` is the type of the target data,

- argument `[source]` can be any Abel container,

- argument `[target]` is a `string` type should the `source` be a `abel::Dict`,
  and a `integer` should the `[source]` be a `abel::List`.

Well, we must face the reality that C++ is a strong-typed language. We are
compelled to clarify the data type we want, which is perhaps not a bad thing.

Examples can be found in directory `examples/standard_json/`.

## Abel `JSON+` parser

The so-called `JSON+` data format has the following features. `JSON+` format
is very similar to `JSON` in terms of data structure. However,

- `JSON+` allows comment lines or inline comments. Any text that appears
  after symbol `#` is considered as comment.

- `JSON+` accepts more data types. In addition to the standard `Null`, `Bool`,
  `Double`,`Text` (string), current version of `JSON+` also recognises
  `Integer`, `Complex`, `Binary`, and `Bitstring`.

### Parsing, loading, and gettting

The *parsing*, *loading*, and *getting* process is identical to the above.
The only exception is that you must use a dedicated parser class
`abel::JsonPlusParser` and a dedicated loader class `abel::JsonPlusLoader`.

The getter and its usage remain the same.

Examples can be found in directory `examples/json_plus/`.

## Version information

- Version: 0.0.1

- Updated: 10 October 2022.

- Compile: g++ 9.4.0 on Ubuntu 20.04 / clang Apple LLVM 9.1.0 (clang-902.0.39.2)

## Compile

To compile with Abel library, the only required header is `abel.hpp`.
The `Makefile` creates in directory `/build` a shared library named `libabel.so`.