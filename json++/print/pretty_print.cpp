#include "pretty_print.hpp"
#include "basic_print.hpp"
#include "functional/compound.hpp"


std::ostream& pretty_print_number(std::ostream &os, const jpp::number_type &num)
{
    return os << num;
}

/*
std::ostream& pretty_print_array(std::ostream&, const jpp::array_type&, unsigned indent = jpp::DEFAULT_INDENT);
std::ostream& pretty_print_object(std::ostream&, const jpp::object_type&, unsigned indent = jpp::DEFAULT_INDENT);
*/

std::ostream& pretty_print(std::ostream &stream, const jpp::json &json_value, unsigned indent)
{
    using namespace jpp;

    return std::visit(fun::compound(
        [&] (const null_type &v) -> std::ostream& { return print_null(stream, v); },
        [&] (const boolean_type &v) -> std::ostream& { return print_boolean(stream, v); },
        [&] (const number_type &v) -> std::ostream& { return pretty_print_number(stream, v); },
        [&] (const string_type &v) -> std::ostream& { return print_string(stream, v); },
        [&] (const array_type &v)  -> std::ostream& { return print_array(stream, v, indent); },
        [&] (const object_type &v) -> std::ostream& { return print_object(stream, v, indent); }
    ), json_value.value);
}
