#include <cstddef>
#include <string>
#include <vector>

#pragma once

namespace ecc {

// 通过第二个参数提供的字符集分割字符串，且出现在字符集中的字符都被去除。
std::vector<std::string> s_split(const std::string &tar, const char *ss) {
    std::vector<std::string> vstrs;
    size_t left = 0;
    size_t temp = 0;
    while (1) {
        left = tar.find_first_not_of(ss, left);
        if (left == std::string::npos)
            break;
        temp = tar.find_first_of(ss, left);
        if (temp == std::string::npos) {
            vstrs.emplace_back(std::move(tar.substr(left)));
            break;
        } else {
            vstrs.emplace_back(std::move(tar.substr(left, temp - left)));
            left = temp;
        }
    }
    return std::move(vstrs);
}

std::string s_split(const std::string &tar, const char *ss, int which) {
    return std::move(s_split(tar, ss)[which]);
}

} // namespace ecc