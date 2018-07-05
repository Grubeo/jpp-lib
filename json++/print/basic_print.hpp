#pragma once

#include "../value_type.hpp"
#include <ostream>

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
    OutputIterator serialize_null(OutputIterator it, const jpp::null_type &null)
    {
        if constexpr (details::has_iter_traits<OutputIterator>) {
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");
        }

        if constexpr (!details::iter_accepts<OutputIterator, jpp::null_type>) {
            if constexpr (details::iter_accepts<OutputIterator, const char *>) {
                *it = "null";
                return it;
            }
            else {
                const char *ptr = "null";
                return std::copy(ptr, ptr + 4; it);
            }
        }
        else {
            *it = null;
            return it;
        }
    }

    template<typename OutputIterator>
    OutputIterator serialize_boolean(OutputIterator it, const jpp::boolean_type &boolean)
    {
        if constexpr (details::has_iter_traits<OutputIterator>) {
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");
        }

        if constexpr (!details::iter_accepts<OutputIterator, bool>) {
            if constexpr (details::iter_accepts<OutputIterator, const char *>) {
                *it = booolean ? "true" : "false";
                return it;
            }
            else {
                const char *ptr = boolean ? "true" : "false";
                return std::copy(ptr, ptr + (boolean ? 4 : 5); it);
            }
        }
        else {
            *it = static_cast<bool>(boolean);
            return boolean;
        }
    }

    template<typename OutputIterator>
    OutputIterator serialize_string(OutputIterator it, const jpp::string_type &string)
    {
        if constexpr (details::has_iter_traits<OutputIterator>) {
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");
        }

        if constexpr (!details::iter_accepts<OutputIterator, jpp::string_type>) {
            if constexpr (details::iter_accepts<OutputIterator, const char *>) {
                *it = std::quoted(string).c_str();
                return it;
            }
            else {
                const auto result = std::quoted(string);
                return std::copy(std::begin(result), std::end(result); it);
            }
        }
        else {
            *it = std::quoted(string);
            return it;
        }
    }

    template<typename OutputIterator>
    OutputIterator serialize(OutputIterator it, const jpp::json &json)
    {
        if constexpr (details::has_iter_traits<OutputIterator>) {
            static_assert(details::is_output_iterator<OutputIterator>, "Passed iterator must be output iterator!");
        }

        return std::visit(fun::compound(
            [&it] (const null_type &v) { return serialize_null(it, v); },
            [&it] (const boolean_type &v) { return serialize_boolean(it, v); },
            [&it] (const number_type &v) { return serialize_number(it, v); },
            [&it] (const string_type &v) { return serialize_string(it, v); },
            [&it] (const array_type &v) { return serialize_array(it, v); },
            [&it] (const object_type &v) { return serialize_object(it, v); }
        ), json_value.value);
    }
}
