#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

namespace ecc {

void print() {}

// 打印
template <typename T>
void print(T &&t) {
    std::cout << std::forward<T>(t);
}

// 打印
template <typename T, typename... Args>
void print(T &&t, Args &&...argv) {
    std::cout << std::forward<T>(t);
    print(std::forward<Args>(argv)...);
}

void println() { std::cout << "\n"; }

// 打印并换行
template <typename T>
void println(T &&t) {
    print(std::forward<T>(t));
    std::cout << "\n";
}

// 打印并换行
template <typename T, typename... Args>
void println(T &&t, Args &&...argv) {
    std::cout << std::forward<T>(t);
    println(std::forward<Args>(argv)...);
}

// 打印错误，以[EasyCC ERROR]开头
void perror(const char *err) {
    static const char *err_head = "[EasyCC ERROR]: ";
    println(err_head, err);
    abort();
}

// 刷新缓冲区
void pflush() { std::cout << std::flush; }

} // namespace ecc