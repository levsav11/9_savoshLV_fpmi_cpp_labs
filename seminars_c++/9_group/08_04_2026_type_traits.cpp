#include <iostream>
#include <type_traits>


template <typename U, typename V>
struct is_same {
    static const bool value = false;
};


template <typename U>
struct is_same<U, U> {
    static const bool value = true; 
};

//c++14
template <typename U, typename V>
static const bool is_same_v = is_same<U, V>::value;


template <typename U, typename V>
void f() {

   // .....
   //
   if (is_same_v<U, V>) {
       std::cout << "same";
    } else {
       std::cout << "not same";
    }
}



int main() {

    f<int, double>();
    f<int, int>();

    return 0;
}

