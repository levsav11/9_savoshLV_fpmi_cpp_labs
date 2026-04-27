#include <iostream>
#include <map>
#include <string>

namespace utils {
template <typename T>
T my_max(T x, T y) {
    return x > y ? x : y;
}
}

template <typename T>
using mymap = std::map<T, T>; // c++11


template <typename T>
const T pi = 3.1415926; // c++14


int main() {

    mymap<int> mp;

    std::cout << pi<int>;

    int x = 6;
    double y = 7;
    std::cout << utils::my_max<double>(x, y) << '\n';

    std::string s1 = "abc";
    std::string s2 = "def";
    std::cout << utils::my_max(s1, s2);

    return 0;
}
