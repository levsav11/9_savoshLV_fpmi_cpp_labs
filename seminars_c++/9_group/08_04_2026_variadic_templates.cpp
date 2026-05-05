#include <ctime>
#include <iostream>


//template <typename... Args>
//void print(Args... args) {
//}

void print() {}

template <typename Head, typename... Tail>
void print(const Head& head, const Tail&... tail) {
    std::cout << head << ' ';
    print(tail...);
}


int main() {

    print(1, 2u, 3.14f, 'f', "abc");

    return 0;
}
