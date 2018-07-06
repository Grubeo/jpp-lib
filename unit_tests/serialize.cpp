#include <boost/test/unit_test.hpp>

#include "../json++/value_type.hpp"
#include "../json++/print/basic_print.hpp"

BOOST_AUTO_TEST_CASE(serialize_null_vector)
{
    jpp::null_type nullvalue = jpp::null;
    std::vector<std::string> strings;
    jpp::serialize_null(std::back_inserter(strings), nullvalue);
    BOOST_REQUIRE(strings.front() == "null");
}

BOOST_AUTO_TEST_CASE(serialize_null_string)
{
    jpp::null_type nullvalue = jpp::null;
    std::string str;
    jpp::serialize_null(std::back_inserter(str), nullvalue);
    BOOST_REQUIRE(str == "null");
}

BOOST_AUTO_TEST_CASE(serialize_boolean_vector)
{
    {
        jpp::boolean_type boolean = false;
        std::vector<std::string> strings;
        jpp::serialize_boolean(std::back_inserter(strings), boolean);
        BOOST_REQUIRE(strings.front() == "false");
    }
    {
        jpp::boolean_type boolean = true;
        std::vector<std::string> strings;
        jpp::serialize_boolean(std::back_inserter(strings), boolean);
        BOOST_REQUIRE(strings.front() == "true");
    }
}

BOOST_AUTO_TEST_CASE(serialize_boolean_string)
{
    {
        jpp::boolean_type boolean = false;
        std::string str;
        jpp::serialize_boolean(std::back_inserter(str), boolean);
        BOOST_REQUIRE(str == "false");
    }
    {
        jpp::boolean_type boolean = true;
        std::string str;
        jpp::serialize_boolean(std::back_inserter(str), boolean);
        BOOST_REQUIRE(str == "true");
    }
}
