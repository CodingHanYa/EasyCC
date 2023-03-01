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