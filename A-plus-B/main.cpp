#include <iostream>

const int MAX = 100000;

int A[MAX], B[MAX], C[MAX];

int main() {
    std::ios::sync_with_stdio(false);

    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++)
        std::cin >> A[i];

    for (int i = 0; i < N; i++)
        std::cin >> B[i];

    for (int i = 0; i < N; i++)
        std::cin >> C[i];

    unsigned long long count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                if (A[i] + B[j] == C[k])
                    count++;

    std::cout << count << std::endl;

    return 0;
}
