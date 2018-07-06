#include <boost/test/unit_test.hpp>

#include "../json++/value_type.hpp"
#include "../json++/print/basic_print.hpp"

BOOST_AUTO_TEST_CASE(serialize_null_to_vector)
{
    jpp::null_type nullvalue = jpp::null;
    std::vector<std::string> strings;
    jpp::serialize_null(std::back_inserter(strings), nullvalue);
    BOOST_REQUIRE(strings.front() == "null");
}

BOOST_AUTO_TEST_CASE(serialize_null_to_string)
{
    jpp::null_type nullvalue = jpp::null;
    std::string str;
    jpp::serialize_null(std::back_inserter(str), nullvalue);
    BOOST_REQUIRE(str == "null");
}

BOOST_AUTO_TEST_CASE(serialize_boolean_to_vector)
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

BOOST_AUTO_TEST_CASE(serialize_boolean_to_string)
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

BOOST_AUTO_TEST_CASE(serialize_string_to_string)
{
    std::string target;
    jpp::string_type string = "Hello World";
    jpp::serialize_string(std::back_inserter(target), string);
    BOOST_REQUIRE(target == "\"Hello World\"");
}

BOOST_AUTO_TEST_CASE(serialize_string_to_vector)
{
    std::vector<std::string> target;
    jpp::string_type string = "Hello World";
    
    jpp::serialize_string(std::back_inserter(target), string);
    BOOST_REQUIRE(target.front() == "\"Hello World\"");
}

BOOST_AUTO_TEST_CASE(serialize_array_to_string)
{
    std::string target;
    jpp::array_type array { jpp::string_type{ "Hello" }, jpp::boolean_type{true}, jpp::string_type{"World"} };
    jpp::serialize_array(std::back_inserter(target), array);
    BOOST_REQUIRE(target == "[\"Hello\",true,\"World\"]");
}

BOOST_AUTO_TEST_CASE(serialize_array_to_vector)
{
    std::vector<std::string> target;
    jpp::array_type array { jpp::string_type{ "Hello" }, jpp::boolean_type{true}, jpp::string_type{"World"} };
    jpp::serialize_array(std::back_inserter(target), array);
    const auto joined = std::accumulate(std::begin(target), std::end(target), std::string{}, std::plus<>{});
    BOOST_REQUIRE(joined == "[\"Hello\",true,\"World\"]");
}
