#include <iostream>

template <typename T>
class Victor {
    T x;
};

// patrial specialization
template <typename T>
class Victor<const T> {

};


// full specialization
template <>
class Victor<bool>{};


template <typename U, typename V>
class S{};




template <typename U, typename V>
void f(U, V);


template <typename T>
void f(T, T);


template <>
foid f(int, int);




template <typename T = int, size_t N = 5>
class array{};



int main() {
    
    array a; // array<int, 5>

    return 0;
}
