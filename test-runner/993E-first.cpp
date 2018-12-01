#include <iostream>
#include <cstring>

typedef long long ll;

const ll MAX = 300000;

ll C[MAX];
ll zero_count = 0;
ll n, x;

void init(ll n) {
    std::memset(C, 0, (n + 1)* sizeof(ll));
    C[0] = 1;
}

void input() {
    std::cin >> n >> x;
    init(n);

    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        ll v;
        std::cin >> v;
        sum += v < x;
        C[sum]++;
    }

    for (ll i = 0; i <= sum; i++)
        if (C[i] > 1) 
            zero_count += C[i] * (C[i] - 1) / 2;
}

int main() {
    input();
    std::cout << zero_count << " ";
    for (ll k = 1; k <= n; k++) {
        ll count = 0;
        for (ll i = 0; i <= n - k; i++)
            count += C[i] * C[i + k];
        std::cout << count << " ";
    }
    std::cout << std::endl;
    return 0;
}
