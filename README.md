# jpp-lib - development version
Target is the most performance library for parsing json files in the world for C++ hardcore-optimization fans. 
This library is **under development** so coding style, file structure and everything else **may change**.

## Goals of this project
* usage of STL-like iterators for input and output
* convinient functions to provide nice loooking usecases
* fast runtime usage
* (distant future) constexpr modeling of JSON structure for quick loading of application settings

## Compilation
Just run compile.js script in [nodejs](https://nodejs.org/en/). That will build all modules to *.o files and an current development example about this library.

## Requiments
* g++ supporting C++17 (std::variant for example)
* optional: nodejs for auto-compiling and POSIX system for example io_handling

## Library style
Because different library users may want to use different style for using library, we must ensure that we have all convenient APIs. One of examples is listed below.

```c++
namespace jpp
{
    // iostream style
    std::ostream& print_null(std::ostream&, const null_type&);
    std::ostream& print_boolean(std::ostream&, const boolean_type&);
    std::ostream& print_number(std::ostream&, const number_type&);
    std::ostream& print_string(std::ostream&, const string_type&);
    std::ostream& print_array(std::ostream&, const array_type&);
    std::ostream& print_object(std::ostream&, const object_type&);
    std::ostream& print(std::ostream&, const json&);

    // STL style
    template<typename OutputIterator> OutputIterator serialize_null(OutputIterator, const null_type&);
    template<typename OutputIterator> OutputIterator serialize_boolean(OutputIterator, const boolean_type&);
    template<typename OutputIterator> OutputIterator serialize_number(OutputIterator, const number_type&);
    template<typename OutputIterator> OutputIterator serialize_string(OutputIterator, const string_type&);
    template<typename OutputIterator> OutputIterator serialize_array(OutputIterator, const array_type&);
    template<typename OutputIterator> OutputIterator serialize_object(OutputIterator, const object_type&);
    template<typename OutputIterator> OutputIterator serialize(OutputIterator, const json&);

    // std::string return value style
    std::string serialize_null(const null_type&);
    std::string serialize_boolean(const boolean_type&);
    std::string serialize_number(const number_type&);
    std::string serialize_string(const string_type&);
    std::string serialize_array(const array_type&);
    std::string serialize_object(const object_type&);
    std::string serialize(const json&);
}
```
