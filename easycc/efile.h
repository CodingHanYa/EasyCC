#pragma once
#include "./etype_traits.h"
#include <fstream>
#include <string>
#include <vector>

namespace ecc {

class EasyFile {
    std::vector<std::string> form;
    std::fstream file;

public:
    explicit EasyFile(const char *path, std::ios_base::openmode mode) { file.open(path, mode); }
    EasyFile() { file.close(); }

public:
    // 判断是否打开
    bool is_open() { return file.is_open(); }

    // 加载内容
    void load_into_memory() {
        std::string line;
        while (getline(file, line)) {
            form.emplace_back(std::move(line));
        }
    }
    // 获取行数
    int line_amount() { return form.size(); }

    void write(const char *ss, std::streamsize n) { file.write(ss, n); }

public:
    // 重载遍历
    std::string &operator[](int index) { return form[index]; }

public:
    // 算法简化
    template <typename F,
              typename = typename ecc::tmp::enable_if_t<ecc::tmp::is_runnable_v<typename std::remove_const<F>::type, std::string &>>>
    void for_each_line(F &&deal) {
        for (auto &line : form) {
            deal(line);
        }
    }
};

} // namespace ecc