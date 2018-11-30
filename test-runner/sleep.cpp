#include <thread>
#include <chrono>

using std::chrono::seconds;

int main() {
    std::this_thread::sleep_for(seconds{3});
    return 0;
}
