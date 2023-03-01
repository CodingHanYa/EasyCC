#include "../easycc/eio.h"
#include "../easycc/etype_traits.h"

template <typename F, typename = typename std::enable_if<ecc::tmp::is_runnable_v<F>>::type>
void run_something(F &&foo) {
    foo();
}
int main() {
    run_something([]() { ecc::println("hello world"); });
}