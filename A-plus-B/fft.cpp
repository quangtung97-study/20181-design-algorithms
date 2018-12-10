#include <iostream>
#include <bitset>
#include <complex>
#include <cstring>

typedef std::complex<double> cp;
typedef long long ll;

const int MAX = 50000;
const double PI = 3.14159265358979323846;

const ll MAX_BIT_COUNT = 18;
const ll FFT_MAX = 1 << MAX_BIT_COUNT;

cp A[FFT_MAX], B[FFT_MAX];
int C[FFT_MAX];
ll T[FFT_MAX];

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

void init_T(ll bit_count) {
    ll N = 1 << bit_count;
    for (ll i = 0; i < N; i++) {
        T[i] = reverse(i, bit_count).to_ullong();
    }
}

void fft(cp *A, ll bit_count, bool inverse = false) {
    static cp W[FFT_MAX];

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

void init() {
    std::memset(A, 0, sizeof(cp) * FFT_MAX);
    std::memset(B, 0, sizeof(cp) * FFT_MAX);
    std::memset(C, 0, sizeof(int) * FFT_MAX);
}

int main() {
    std::ios::sync_with_stdio(false);

    init();
    init_T(MAX_BIT_COUNT);

    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        int x; std::cin >> x;
        A[x + MAX] += 1;
    }

    for (int i = 0; i < N; i++) {
        int x; std::cin >> x;
        B[x + MAX] += 1;
    }

    for (int i = 0; i < N; i++) {
        int x; std::cin >> x;
        C[x + 2*MAX] += 1;
    }

    fft(A, MAX_BIT_COUNT);
    fft(B, MAX_BIT_COUNT);

    for (ll i = 0; i < FFT_MAX; i++)
        A[i] *= B[i];

    fft(A, MAX_BIT_COUNT, true);

    ll count = 0;
    for (int x = MAX; x <= 3 * MAX; x++)
        count += std::llround(A[x].real()) * C[x];

    std::cout << count << std::endl;

    return 0;
}
