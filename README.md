# 简介

EasyCC 是用 C++11 编写的工具库(util)，主要包括基于 SFINAE 的元函数封装，以及简便的 IO 接口、字符串操作、文件操作等。
EasyCC 只需导入头文件即可直接编译使用，非常方便。

## Demo（from `EasyCC/tiny_demo/`）

### IO

```C++
#include "../easycc/eio.h"
int main() {
    ecc::println(" =============================== ");
    ecc::print(" *     EasyCC Version 0.1      * \n");
    ecc::println(" =============================== ");
}
```

### TMP

```C++
#include "../easycc/eio.h"
#include "../easycc/etype_traits.h"

template <typename F, typename = typename std::enable_if<ecc::tmp::is_runnable_v<F>>::type>
void run_something(F &&foo) {
    foo();
}
int main() {
    run_something([]() { ecc::println("hello world"); });
}

```

### String

```C++
#include "../easycc/eio.h"
#include "../easycc/estring.h"

int main() {
    std::string s = "/home/Hanya/code/EasyCC";
    auto str_vec = ecc::s_split(s, "/");
    for (auto &str : str_vec) {
        ecc::print('|');
        ecc::print(str);
    }
    ecc::println("|");
    // |home|Hanya|code|EasyCC|
}
```

### File

```C++
#include "../easycc/efile.h"
#include "../easycc/eio.h"

int main() {
    ecc::EasyFile f("./easy_io.cc", std::ios::in);
    if (f.is_open()) {
        f.load_into_memory();
        f.for_each_line([](const std::string &line) { ecc::println(line); });
    } else {
        ecc::perror("Failed to open file");
    }
}
```

## TMP Support：

```C++
tmp::void_t<>      // 转化为void
tmp::enable_if_t<> // 等于在C++14以上出现的std::enable_if_t

tmp::has_member_funtion_begin<>  // 是否有成员函数begin()
tmp::has_member_funtion_end<>    // 是否有成员函数end()

tmp::is_runnable<> // 是否是可执行对象
tmp::is_return<>   // 是否返回某类型

tmp::is_reference_wrapper<> // 是否是一个引用包装器
```

## 最后

目前该库功能较为简单，只是在我写毕业论文操作数据时提供了一些帮助。今后希望大家可以一起出力，共同维护。
