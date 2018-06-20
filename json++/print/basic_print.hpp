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

    std::ostream& print(std::ostream&, const json&);
}