#ifndef TEST_HELPER_HPP
#define TEST_HELPER_HPP

#include <istream>
#include <string>
#include <vector>

typedef void (*callback_handler)(std::istream& result, std::istream& actual);

void test_with(
        const std::string& input_path, 
        const std::string& output_path,
        callback_handler handler);

std::vector<std::string> all_test_cases();

#endif
