#include <boost/test/unit_test.hpp>

#include "../json++/value_type.hpp"
#include "../json++/print/basic_print.hpp"

#include <numeric>

BOOST_AUTO_TEST_SUITE(SerializeFunctions)

BOOST_AUTO_TEST_CASE(NullToVector)
{
    jpp::null_type nullvalue = jpp::null;
    std::vector<std::string> strings;
    jpp::serialize_null(std::back_inserter(strings), nullvalue);
    BOOST_REQUIRE(strings.front() == "null");
}

BOOST_AUTO_TEST_CASE(NullToString)
{
    jpp::null_type nullvalue = jpp::null;
    std::string str;
    jpp::serialize_null(std::back_inserter(str), nullvalue);
    BOOST_REQUIRE(str == "null");
}

BOOST_AUTO_TEST_CASE(BooleanToVector)
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

BOOST_AUTO_TEST_CASE(BooleanToString)
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

BOOST_AUTO_TEST_CASE(StringToString)
{
    std::string target;
    jpp::string_type string = "Hello World";
    jpp::serialize_string(std::back_inserter(target), string);
    BOOST_REQUIRE(target == "\"Hello World\"");
}

BOOST_AUTO_TEST_CASE(StringToVector)
{
    std::vector<std::string> target;
    jpp::string_type string = "Hello World";
    
    jpp::serialize_string(std::back_inserter(target), string);
    BOOST_REQUIRE(target.front() == "\"Hello World\"");
}

BOOST_AUTO_TEST_CASE(ArrayToString)
{
    std::string target;
    jpp::array_type array { jpp::string_type{ "Hello" }, jpp::boolean_type{true}, jpp::string_type{"World"} };
    jpp::serialize_array(std::back_inserter(target), array);
    BOOST_REQUIRE(target == "[\"Hello\",true,\"World\"]");
}

BOOST_AUTO_TEST_CASE(ArrayToVector)
{
    std::vector<std::string> target;
    jpp::array_type array { jpp::string_type{ "Hello" }, jpp::boolean_type{true}, jpp::string_type{"World"} };
    jpp::serialize_array(std::back_inserter(target), array);
    const auto joined = std::accumulate(std::begin(target), std::end(target), std::string{}, std::plus<>{});
    BOOST_REQUIRE(joined == "[\"Hello\",true,\"World\"]");
}

BOOST_AUTO_TEST_CASE(ObjectToString)
{
    std::string target;
    jpp::object_type object { { jpp::string_type{ "Hello" }, jpp::boolean_type{true} }, { jpp::string_type{ "World" }, jpp::null } };
    jpp::serialize_object(std::back_inserter(target), object);
    BOOST_REQUIRE(target == "{\"Hello\":true,\"World\":null}");
}

BOOST_AUTO_TEST_CASE(ObjectToVector)
{
    std::vector<std::string> target;
    jpp::object_type object { { jpp::string_type{ "Hello" }, jpp::boolean_type{true} }, { jpp::string_type{ "World" }, jpp::null } };
    jpp::serialize_object(std::back_inserter(target), object);
    const auto joined = std::accumulate(std::begin(target), std::end(target), std::string{}, std::plus<>{});
    BOOST_REQUIRE(joined == "{\"Hello\":true,\"World\":null}");
}

BOOST_AUTO_TEST_SUITE_END()