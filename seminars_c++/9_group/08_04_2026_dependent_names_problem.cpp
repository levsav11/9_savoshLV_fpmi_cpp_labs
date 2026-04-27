#include <iostream>
#include <vector>

template <typename T>
struct S {
    using X = T;
};

template <>
struct S<int> {
    static int X;
};

int a = 0;

template <typename T>
void f() {
   S<T>::X* a; //  f<int>(), f<dobule> 
}



int main() {

    f<double>();

    return 0;
}
