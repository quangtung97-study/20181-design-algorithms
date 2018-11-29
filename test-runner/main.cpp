#include "test_helper.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

typedef long long ll;

std::ostream& operator << (std::ostream& out, 
        const std::vector<ll>& vec)
{
    for (auto e: vec)
        std::cout << e << " ";
    return out;
}

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

static void handle_output(
        std::istream& result, std::istream& actual) {
    std::vector<ll> A, B;

    ll x;
    while (result >> x) {
        A.push_back(x);
    }

    while (actual >> x) {
        B.push_back(x);
    }

    auto equal = std::equal(A.begin(), A.end(), B.begin(), B.end());
    if (equal) {
        std::cout << KGRN;
        std::cout << "PASSED" << std::endl;
        std::cout << KNRM;
    }
    else {
        std::cout << KRED;
        std::cout << "FAILED" << std::endl;
        std::cout << "Output: " << A << std::endl;
        std::cout << "Actual: " << B << std::endl;
        std::cout << KNRM;
    }

}

int main(int argc, char **argv) {
    std::ios::sync_with_stdio(false);
    if (argc <= 1) {
        std::cout << "Thieu ma nguon chuong trinh" << std::endl;
        exit(-1);
    }

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
        std::cout << "Test case: " << dir << std::endl;
        test_with(input, output, handle_output);
    }
    return 0;
}
