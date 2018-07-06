#pragma once

#include "../value_type.hpp"
#include "../functional/compound.hpp"
#include <ostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <sstream>
#include <tuple>

namespace jpp
{
    std::ostream& print_null(std::ostream&, const null_type&);
    std::ostream& print_boolean(std::ostream&, const boolean_type&);
    std::ostream& print_number(std::ostream&, const number_type&);
    std::ostream& print_string(std::ostream&, const string_type&);
    std::ostream& print_array(std::ostream&, const array_type&);
    std::ostream& print_object(std::ostream&, const object_type&);

    std::ostream& print_json(std::ostream&, const json&);

    namespace details
    {
        template< typename, typename,  typename = std::void_t<> >
        struct iter_accepts_type : std::false_type
        {
        };
        
        template< typename T, typename Target >
        struct iter_accepts_type<T, Target, 
            std::void_t<decltype(*std::declval<T>() = std::declval<Target>())>> 
            : std::true_type
        {
        };

        template<typename OutIt, typename Target>
        constexpr bool iter_accepts = iter_accepts_type<OutIt, Target>::value;

        template< typename,  typename = std::void_t<> >
        struct has_iterator_traits : std::false_type
        {
        };
        
        template<typename T>
        struct has_iterator_traits
            <T, std::void_t<typename std::iterator_traits<T>::iterator_category>> 
            : std::true_type
        {
        };

        template<typename Iterator>
        constexpr auto is_output_iterator = 
            std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category, 
                std::output_iterator_tag>;

        template<typename Iterator>
        constexpr auto has_iter_traits = has_iterator_traits<Iterator>::value;
    }

    template<typename OutputIterator>
    OutputIterator serialize(OutputIterator it, const jpp::json &json);

    template<typename OutputIterator>
    OutputIterator serialize_null(OutputIterator it, const jpp::null_type &)
    {
        if constexpr (details::has_iter_traits<OutputIterator>)
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");


        if constexpr (details::iter_accepts<OutputIterator, const char *>) {
            *it = "null";
            return it;
        }
        else {
            const char *ptr = "null";
            return std::copy(ptr, ptr + 4, it);
        }
    }

    template<typename OutputIterator>
    OutputIterator serialize_boolean(OutputIterator it, const jpp::boolean_type &boolean)
    {
        if constexpr (details::has_iter_traits<OutputIterator>)
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");


        if constexpr (details::iter_accepts<OutputIterator, const char *>) {
            *it = boolean ? "true" : "false";
            return it;
        }
        else {
            const char *ptr = boolean ? "true" : "false";
            return std::copy(ptr, ptr + (boolean ? 4 : 5), it);
        }
    }

    
    template<typename OutputIterator>
    OutputIterator serialize_string(OutputIterator it, const jpp::string_type &str)
    {
        if constexpr (details::has_iter_traits<OutputIterator>)
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");

        std::ostringstream oss;
        oss << std::quoted(str);

        if constexpr (details::iter_accepts<OutputIterator, std::string>) {
            *it = std::move(oss).str();
            return it;
        }
        else {
            const std::string result = std::move(oss).str();
            return std::copy(std::begin(result), std::end(result), it);
        }
    }

    template<typename OutputIterator>
    OutputIterator serialize_array(OutputIterator it, const jpp::array_type &array)
    {
        if constexpr (details::has_iter_traits<OutputIterator>)
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");
            
        const auto end = std::prev(std::end(array));

        constexpr const auto chars = [] {
            if constexpr (details::iter_accepts<OutputIterator, char>) return std::tuple { '[', ',', ']' };
            else return std::tuple { "[", ",", "]" };
        }();
        
        *it = std::get<0>(chars);

        std::for_each(std::begin(array), end, [&it, separator = std::get<1>(chars)](auto &e) { 
            *jpp::serialize(it, e) = separator; });

        *jpp::serialize(it, *end) = std::get<2>(chars);

        return it;
    }
    
    template<typename OutputIterator>
    OutputIterator serialize_number(OutputIterator it, [[maybe_unused]] const jpp::number_type &json)
    {
        return it;
    }

    template<typename OutputIterator>
    OutputIterator serialize_object(OutputIterator output, const jpp::object_type &object)
    {
        if constexpr (details::has_iter_traits<OutputIterator>)
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");

        const auto end = std::prev(std::end(object));

        constexpr const auto chars = [] {
            if constexpr (details::iter_accepts<OutputIterator, char>) return std::tuple { '{', ',', ':', '}' };
            else return std::tuple { "{", ",", ":", "}" };
        }();
        
        *output = std::get<0>(chars);

        for (auto it = std::begin(object); it != end; ++it) {
            *jpp::serialize_string(output, it->first) = std::get<2>(chars);
            *jpp::serialize(output, it->second) = std::get<1>(chars);
        }

        *jpp::serialize_string(output, end->first) = std::get<2>(chars);
        *jpp::serialize(output, end->second) = std::get<3>(chars);

        return output;
    }

    template<typename OutputIterator>
    OutputIterator serialize(OutputIterator it, const jpp::json &json)
    {
        if constexpr (details::has_iter_traits<OutputIterator>)
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");

        const auto visitor = fun::compound(
            [&it] (const jpp::null_type &v) { jpp::serialize_null(it, v); },
            [&it] (const jpp::boolean_type &v) { jpp::serialize_boolean(it, v); },
            [&it] (const jpp::number_type &v) { jpp::serialize_number(it, v); },
            [&it] (const jpp::string_type &v) { jpp::serialize_string(it, v); },
            [&it] (const jpp::array_type &v) { jpp::serialize_array(it, v); },
            [&it] (const jpp::object_type &v) { jpp::serialize_object(it, v); }
        );

        std::visit(visitor, json.value);

        return it;
    }
}
