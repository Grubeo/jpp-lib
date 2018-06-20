#include <ostream>

#include "basic_print.hpp"
#include "../value_type.hpp"

namespace jpp
{
    constexpr unsigned DEFAULT_INDENT = 2;

    std::ostream& pretty_print_number(std::ostream&, const jpp::number_type&);
    std::ostream& pretty_print_array(std::ostream&, const jpp::array_type&, unsigned indent = DEFAULT_INDENT);
    std::ostream& pretty_print_object(std::ostream&, const jpp::object_type&, unsigned indent = DEFAULT_INDENT);    
    std::ostream& pretty_print(std::ostream&, const jpp::json&, unsigned indent = DEFAULT_INDENT);

    namespace pretty_print_operators
    {
        inline std::ostream& operator<<(std::ostream &stream, const jpp::json &value)
        {
            return pretty_print(stream, value, DEFAULT_INDENT);
        }
    }
}
