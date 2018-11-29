#include "test_helper.hpp"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <dirent.h>

using std::chrono::steady_clock;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::duration_cast;

static bool is_child(int pid) {
    return pid == 0;
}

static void redirect(int oldfd, int newfd) {
    int res = ::dup2(oldfd, newfd);
    if (res == -1)
        exit(-1);
    ::close(oldfd);
}

static void child(int *in_fd, int *out_fd) {
    ::close(in_fd[1]);
    ::close(out_fd[0]);


    redirect(in_fd[0], 0);
    redirect(out_fd[1], 1);

    char *argv[] = {(char *)"program", NULL};
    ::execv("./program", argv);
}

static std::string read_from_file(const std::string& path) {
    std::string result;
    std::ifstream file(path, std::ios::binary);

    const size_t BUFF_SIZE = 4096;
    char buff[BUFF_SIZE];
    size_t count;
    do {
        file.read(buff, BUFF_SIZE);
        count = file.gcount();
        std::copy(buff, buff + count, std::back_inserter(result));
    } while (count != 0);

    return result;
}

static void write_to(int fd, const std::string& s) {
    const size_t BUFF_SIZE = 4096;
    size_t size = s.size();
    const char *data = s.c_str();
    while (size != 0) {
        auto count = std::min(BUFF_SIZE, size);
        ::write(fd, data, count);
        data += count;
        size -= count;
    }
    ::close(fd);
}

static std::string read_from(int fd) {
    std::string result;

    const size_t BUFF_SIZE = 4096;
    char buff[BUFF_SIZE];
    int count;
    do {
        count = ::read(fd, buff, BUFF_SIZE);
        std::copy(buff, buff + count, std::back_inserter(result));
    } while (count > 0);
    ::close(fd);

    return result;
}

static void parent(
        int pid, int *in_fd, int *out_fd, 
        const std::string& input_path,
        const std::string& output_path,
        callback_handler handler
        )
{
    ::close(in_fd[0]);
    ::close(out_fd[1]);

    int input = in_fd[1];
    auto str = read_from_file(input_path);

    auto t0 = steady_clock::now();
    write_to(input, str);
    str = read_from(out_fd[0]);
    int status;
    ::waitpid((pid_t)pid, &status, 0);
    auto t1 = steady_clock::now();

    std::istringstream ss(str);
    std::ifstream actual(output_path, std::ios::binary);
    handler(ss, actual);

    auto delta = t1 - t0;
    seconds s_count= duration_cast<seconds>(delta);
    delta -= s_count;
    milliseconds ms_count = duration_cast<milliseconds>(delta);
    std::cout << "Time: " << s_count.count() << "s "
        << ms_count.count() << "ms" << std::endl;
}

void test_with(
        const std::string& input_path, 
        const std::string& output_path,
        callback_handler handler
        )
{
    int in_fd[2], out_fd[2];
    ::pipe(in_fd);
    ::pipe(out_fd);

    int pid = ::fork();
    if (pid == -1)
        exit(-1);

    if (is_child(pid))
        child(in_fd, out_fd);
    else
        parent(pid, in_fd, out_fd,
                input_path, output_path, handler);
}

std::vector<std::string> all_test_cases() {
    std::vector<std::string> result;

    DIR *d;
    struct dirent *dir;
    d = ::opendir("./test");
    if (d) {
        while ((dir = ::readdir(d)) != NULL) {
            result.push_back(dir->d_name);
        }
        ::closedir(d);
    }

    std::sort(result.begin(), result.end());
    // remove .. and .
    result.erase(result.begin(), result.begin() + 2);
    return result;
}
