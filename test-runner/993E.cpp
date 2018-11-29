#include <cstring>
#include <complex>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <iostream>

typedef std::complex<double> cp;
typedef long long ll;

const ll MAX = 300000;
const double PI = 3.14159265358979323846;
ll T[MAX * 2];

ll ceil_log2(ll n) {
    ll v = 1;
    ll log = 0;
    while (v < n) {
        v <<= 1;
        log++;
    }
    return log;
}

std::bitset<64> reverse(std::bitset<64> set, ll bit_count) {
    for (ll i = 0; i < bit_count / 2; i++) {
        bool tmp = set[i];
        set[i] = set[bit_count - 1 - i];
        set[bit_count - 1 - i] = tmp;
    }
    return set;
}

void fft(cp *A, ll bit_count, bool inverse = false) {
    static cp W[MAX];

    ll N = 1 << bit_count;

    for (ll i = 0; i < N; i++) {
        ll j = T[i];
        if (i < j) 
            std::swap(A[i], A[j]);
    }

    for (ll step = 1; step < N; step <<= 1) {
        double angle = -PI / step;
        if (inverse)
            angle = -angle;

        cp w(1, 0), wn(std::cos(angle), std::sin(angle));
        for (ll i = 0; i < step; i++) {
            W[i] = w;
            w *= wn;
        }

        for (ll start_even = 0; start_even < N; start_even += step * 2) {
            auto start_odd = start_even + step;
            for (ll i = 0; i < step; i++) {
                cp U = A[start_even + i];
                cp V = W[i] * A[start_odd + i]; 
                A[start_even + i] = U + V;
                A[start_odd + i] = U - V;
            }
        }
    }

    if (inverse) {
        for (ll i = 0; i < N; i++)
            A[i] /= N;
    }
}

ll C[MAX];
ll zero_count = 0;
ll n, x;
ll C_len, bit_count, N;

void init() {
    std::fill(C, C + n + 1, 0);
    C[0] = 1;

    C_len = n + 1;
    bit_count = ceil_log2(C_len * 2);
    N = 1 << bit_count;

    for (ll i = 0; i < N; i++) {
        T[i] = reverse(i, bit_count).to_ullong();
    }
}

void input() {
    std::cin >> n >> x;

    init();

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
    std::ios::sync_with_stdio(false);

    input();
    std::cout << zero_count << " ";
    static cp A[MAX * 2], B[MAX * 2];

    std::copy(C, C + C_len, A);
    std::fill(A + C_len, A + N, 0);

    std::fill(B, B + 2 * n - C_len, 0);
    std::reverse_copy(C, C + C_len, B + 2 * n - C_len);
    std::fill(B + 2 * n, B + N, 0);

    fft(A, bit_count);
    fft(B, bit_count);
    for (ll i = 0; i < N; i++)
        A[i] *= B[i];
    fft(A, bit_count, true);
    for (ll k = 1; k <= n; k++)
        std::cout << (ll)std::round(A[2 * n - k - 1].real()) << " ";
    std::cout << '\n';
    return 0;
}
