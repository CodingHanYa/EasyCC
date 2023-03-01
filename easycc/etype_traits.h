#pragma once
#include <functional>
#include <type_traits>

namespace ecc {

namespace tmp {

// 用C++11实现后续版本

template <typename... Ts>
struct make_void {
    typedef void type;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

template <bool C, typename T = void>
using enable_if_t = typename std::enable_if<C, T>::type;

// 用于检验类型为可迭代的标准库容器容器

template <typename C>
using iterator_type_for_begin = decltype(std::declval<C>().begin());

template <typename C, typename = void_t<>>
struct has_member_function_begin : std::false_type {};

template <typename C>
struct has_member_function_begin<C, void_t<iterator_type_for_begin<C>>>
    : std::true_type {};

template <typename C>
using iterator_type_for_end = decltype(std::declval<C>().end());

template <typename C, typename = void_t<>>
struct has_member_function_end : std::false_type {};

template <typename C>
struct has_member_function_end<C, void_t<iterator_type_for_end<C>>>
    : std::true_type {};

template <typename C>
constexpr bool has_member_function_begin_v =
    has_member_function_begin<C>::value;

template <typename C>
constexpr bool has_member_function_end_v = has_member_function_end<C>::value;

template <typename C, typename A = void_t<>, typename B = void_t<>>
struct is_iterable_std_container : std::false_type {};

template <typename C>
struct is_iterable_std_container<C, enable_if_t<has_member_function_begin_v<C>>,
                                 enable_if_t<has_member_function_end_v<C>>>
    : std::true_type {};

template <typename C>
constexpr bool is_iterable_std_container_v =
    is_iterable_std_container<C>::value;

// 用于检验是否是可执行类型

template <typename F, typename... Args>
using is_runnable =
    std::is_constructible<std::function<void(Args...)>,
                          typename std::remove_reference<F>::type>;

template <typename F, typename... Args>
constexpr bool is_runnable_v = is_runnable<F, Args...>::value;

// 用于检验是否返回R类型

template <typename F, typename R>
using is_return = std::is_same<typename std::result_of<F()>::type, R>;

template <typename F, typename R>
constexpr bool is_return_v = is_return<F, R>::value;

// 用于检验是否为引用包装器

template <typename T, typename DT = typename std::decay<T>::type>
struct is_reference_wrapper {

    template <typename X, typename XT = typename X::type>
    static constexpr bool check(X *) {
        return std::is_same<X, std::reference_wrapper<XT>>::value;
    };
    static constexpr bool check(...) { return false; };
    static constexpr bool value = check(static_cast<DT *>(0));
};

template <typename T>
constexpr bool is_reference_wrapper_v = is_reference_wrapper<T>::value;

} // namespace tmp

} // namespace ecc