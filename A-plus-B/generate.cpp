#include <iostream>
#include <random>
#include <cstdlib>

const int MAX = 50000;
std::uniform_int_distribution<int> dist(-MAX, MAX);

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    const int N = 1000;
    std::cout << N << std::endl;

    for (int i = 0; i < N; i++)
        std::cout << dist(gen) << " ";
    std::cout << std::endl;

    for (int i = 0; i < N; i++)
        std::cout << dist(gen) << " ";
    std::cout << std::endl;

    for (int i = 0; i < N; i++)
        std::cout << dist(gen) << " ";
    std::cout << std::endl;

    return 0;
}
