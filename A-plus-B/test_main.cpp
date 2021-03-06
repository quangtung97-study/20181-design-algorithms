#include "test_helper.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

typedef long long ll;

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KBLU  "\x1B[34m"

static void handle_output(
        std::istream& output, std::istream& answer) {
    ll output_count;
    ll answer_count;
    output >> output_count;
    answer >> answer_count;

    auto equal = output_count == answer_count;
    if (equal) {
        std::cout << KGRN;
        std::cout << "PASSED" << std::endl;
        std::cout << KNRM;
    }
    else {
        std::cout << KRED;
        std::cout << "FAILED" << std::endl;
        std::cout << "Output: " << output_count << std::endl;
        std::cout << "Answer: " << answer_count << std::endl;
        std::cout << KNRM;
    }

}

int main(int argc, char **argv) {
    std::ios::sync_with_stdio(false);
    if (argc <= 1) {
        std::cout << "Thieu ma nguon chuong trinh" << std::endl;
        exit(-1);
    }

    set_time_limit(milliseconds{2000});

    std::string cmd = "g++ -std=c++14 -O2 ";
    cmd += argv[1];
    cmd += " -o program";

    int res = std::system(cmd.c_str());
    if (res != 0) 
        exit(-1);

    auto test_cases = all_test_cases();

    for (auto& dir: test_cases) {
        std::string path = "test/";
        path += dir;
        std::string input = path + "/input";
        std::string output = path + "/output";
        std::cout << "=============================================" << std::endl;
        std::cout << KBLU 
            << "Test case: " << dir 
            << KNRM << std::endl;
        test_with(input, output, handle_output);
    }
    return 0;
}
