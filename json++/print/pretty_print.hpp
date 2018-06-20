#include <ostream>

#include "../value_type.hpp"

namespace jpp
{
    constexpr unsigned DEFAULT_INDENT = 2;
    std::ostream& pretty_print(std::ostream&, const jpp::json&, unsigned indent = DEFAULT_INDENT, unsigned currentIndent = 0);

    namespace pretty_print_operators
    {
        inline std::ostream& operator<<(std::ostream &stream, const jpp::json &value)
        {
            return pretty_print(stream, value, DEFAULT_INDENT);
        }
    }
}
