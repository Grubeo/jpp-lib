#pragma once

#include <string>
#include <vector>
#include <map>
#include <variant>
#include <ostream>

namespace jpp
{
    class json;

    using null_type = decltype(nullptr);
    using boolean_type = bool;
    using number_type = double;
    using string_type = std::string;

    using array_type = std::vector<json>;
    using object_type = std::map<string_type, json>;

    using value_type = std::variant<null_type, boolean_type,
        string_type, array_type, object_type>;

    constexpr auto null = null_type{};

    class json
    {
        value_type value;
    public:
        json() : value{null} {}

        template<typename T>
        json(T &&t) : value(std::forward<T>(t)) {}

        json(const value_type &val) : value(val) {}
        json(value_type &&val) : value(val) {}

        json(const json&) = default;
        json(json&&) = default;

        json& operator=(const json&) = default;
        json& operator=(json&&) = default;

        ~json() = default;

        operator value_type& () { return value; }
        operator const value_type& () const { return value; }

        friend std::ostream& print_json(std::ostream&, const json&);
    };
}
