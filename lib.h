#pragma once

#include "version.h"
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>

/**
 * @brief version Получение версии.
 * @return Номер версии.
 */
int version();

// check container
template <typename T>       struct is_container                     : std::false_type   {};
template <typename...T>     struct is_container<std::vector<T...> > : std::true_type    {};
template <typename...T>     struct is_container<std::list<T...> >   : std::true_type    {};

// check the same
template <typename T, typename...Args>              struct is_same_t;
template <typename T>                               struct is_same_t<T>             : std::true_type    {};
template <typename T, typename U, typename...Args>  struct is_same_t<T, U, Args...> : std::false_type   {};
template <typename T, typename...Args>              struct is_same_t<T, T, Args...> : is_same_t<T, Args...>     {};


template<typename T>
unsigned char integralByte(const T& val, const char& n) {
    return (val >> ((8 * n) & 0xFF));
}

/**
 * @brief print_ip Печать ip-адреса в интегральном виде.
 * @tparam T - интегральный тип.
 * @param val - значение ip-адреса.
 */
template <typename T>
std::enable_if_t<std::is_integral<T>::value> print_ip(const T& val) {
    for(auto i = sizeof(T); i-- > 0; ) {
        std::cout << std::to_string(integralByte(val, i)) << (i == 0 ? "" : ".");
    }
    std::cout << std::endl;
}

/**
 * @brief print_ip Печать ip-адреса в строковом виде.
 * @param val - значение ip-адреса.
 */
void print_ip(const std::string& val) {
    std::cout << val << std::endl;
}

template <typename T>
std::enable_if_t<is_container<T>::value> print_ip(const T& val) {
    for(const auto& i: val) {
        std::cout << std::to_string(i) << (&i == &val.back() ? "" : ".");
    }
    std::cout << std::endl;
}

// helper function to print a tuple of any size
template<class Tuple, size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << "." << std::get<N-1>(t);
    }
};
template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};
// end helper function

template <typename...Args>
typename std::enable_if<is_same_t<Args...>::value>::type print_ip(const std::tuple<Args...>& val) {
    TuplePrinter<decltype(val), sizeof...(Args)>::print(val);
    std::cout << std::endl;
}
