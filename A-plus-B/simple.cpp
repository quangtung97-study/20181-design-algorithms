#include <iostream>

typedef long long i64;
const i64 MAX = 100000;

i64 A[MAX], B[MAX], C[MAX];

int main() {
    std::ios::sync_with_stdio(false);

    i64 N;
    std::cin >> N;

    for (i64 i = 0; i < N; i++)
        std::cin >> A[i];

    for (i64 i = 0; i < N; i++)
        std::cin >> B[i];

    for (i64 i = 0; i < N; i++)
        std::cin >> C[i];

    unsigned long long count = 0;
    for (i64 i = 0; i < N; i++)
        for (i64 j = 0; j < N; j++)
            for (i64 k = 0; k < N; k++)
                if (A[i] + B[j] == C[k])
                    count++;

    std::cout << count << std::endl;

    return 0;
}
