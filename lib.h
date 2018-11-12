#pragma once

#include "version.h"
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>

using namespace std;

int version();

// check container
template <typename T>       struct is_container                 : false_type {};
template <typename...T>     struct is_container<vector<T...> >  : true_type {};
template <typename...T>     struct is_container<list<T...> >    : true_type {};

// check the same
template <typename T, typename...Args>              struct is_same_t;
template <typename T>                               struct is_same_t<T> : true_type {};
template <typename T, typename U, typename...Args>  struct is_same_t<T, U, Args...> : false_type {};
template <typename T, typename...Args>              struct is_same_t<T, T, Args...> : is_same_t<T, Args...> {};


template<typename T>
unsigned char integralByte(const T& val, const char& n) {
    return (val >> ((8 * n) & 0xFF));
}

template <typename T>
typename std::enable_if_t<std::is_integral<T>::value> print_ip(const T& val) {
    for(auto i = sizeof(T); i-- > 0; ) {
        cout << to_string(integralByte(val, i)) << (i == 0 ? "" : ".");
    }
    cout << endl;
}

void print_ip(const string& val) {
    cout << val << endl;
}

template <typename T>
typename std::enable_if_t<is_container<T>::value> print_ip(const T& val) {
    for(const auto& i: val) {
        cout << to_string(i) << (&i == &val.back() ? "" : ".");
    }
    cout << endl;
}

// helper function to print a tuple of any size
template<class Tuple, size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N-1>::print(t);
        cout << "." << get<N-1>(t);
    }
};
template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        cout << get<0>(t);
    }
};
// end helper function

template <typename...Args>
typename enable_if<is_same_t<Args...>::value>::type print_ip(const tuple<Args...>& val) {
    TuplePrinter<decltype(val), sizeof...(Args)>::print(val);
    cout << endl;
}
