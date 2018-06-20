#include "basic_print.hpp"
#include "value_type.hpp"

#include <iterator>
#include <iomanip>
#include <numeric>

#include "functional/compound.hpp"

std::ostream& jpp::print_json(std::ostream &stream, const jpp::json &json_value)
{
    using namespace jpp;

    return std::visit(fun::compound(
        [&] (const null_type &v) -> std::ostream& { return print_null(stream, v); },
        [&] (const boolean_type &v) -> std::ostream& { return print_boolean(stream, v); },
        [&] (const number_type &v) -> std::ostream& { return print_number(stream, v); },
        [&] (const string_type &v) -> std::ostream& { return print_string(stream, v); },
        [&] (const array_type &v)  -> std::ostream& { return print_array(stream, v); },
        [&] (const object_type &v) -> std::ostream& { return print_object(stream, v); }
    ), json_value.value);
}

std::ostream& jpp::print_null(std::ostream &os, const jpp::null_type&)
{
    return os.write("null", 4);
}

std::ostream& jpp::print_boolean(std::ostream &os, const jpp::boolean_type &boolean)
{
    if (boolean)
        return os.write("true", 4);
    else
        return os.write("false", 5);
}

std::ostream& jpp::print_number(std::ostream &os, const jpp::number_type &number)
{
    return os << std::fixed << number;
}

std::ostream& jpp::print_string(std::ostream &os, const jpp::string_type &str)
{
    return os << std::quoted(str);
}

std::ostream& jpp::print_array(std::ostream &os, const jpp::array_type &array)
{
    os << '[';

    const auto end = std::prev(std::end(array));

    std::accumulate(std::begin(array), end, std::ref(os), 
        [](auto &first, const auto &second) -> std::ostream& { return jpp::print_json(first, second) << ','; });

    return jpp::print_json(os, *end) << ']';
}

std::ostream& jpp::print_object(std::ostream &os, const jpp::object_type &object)
{
    os << '{';

    const auto end = std::prev(std::end(object));

    for (auto it = std::begin(object); it != end; ++it) {
        jpp::print_string(os, it->first) << ':';
        jpp::print_json(os, it->second) << ',';
    }

    jpp::print_string(os, end->first) << ':';
    jpp::print_json(os, end->second);

    return os << '}';
}
