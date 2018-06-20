#include <iostream>
#include <algorithm>
#include <numeric>

#include "io_handling/MemoryMappedFile.hpp"
#include "json++/value_type.hpp"
#include "json++/print/basic_print.hpp"

#define ERROR(MSG) ("\e[1;91m[ERROR]" MSG "\e[0m\n")

char* getCmdOption(char **begin, char **end, const char *option)
{
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
        return *itr;

    return nullptr;
}

int main()
{
    using namespace std::string_literals;

    jpp::json json = jpp::array_type {
        "Hello"s, "World"s,
        "Goodbye"s, "World"s
    };

    // using basic print that produce 'minified' json
    jpp::print(std::cout, json) << '\n';

    /*
    if (char *path = getCmdOption(argv, argv + argc, "-p"); path != nullptr) {
        std::cout << "Path: " << path << '\n';
        std::cerr << ERROR("This functionality hasn't been implemented yet.");
        return EXIT_FAILURE;
    }*/
}
