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