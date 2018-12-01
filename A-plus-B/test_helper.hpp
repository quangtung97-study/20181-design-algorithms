#ifndef TEST_HELPER_HPP
#define TEST_HELPER_HPP

#include <istream>
#include <string>
#include <vector>
#include <chrono>

using std::chrono::milliseconds;

typedef void (*callback_handler)(std::istream& output, std::istream& answer);

void set_time_limit(milliseconds ms); 

void test_with(
        const std::string& input_path, 
        const std::string& output_path,
        callback_handler handler);

std::vector<std::string> all_test_cases();

#endif
