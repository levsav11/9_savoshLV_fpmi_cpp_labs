#include <iostream>
int main() {
    setlocale(LC_ALL, "RUS");
    long a=0; long b=1; long ch=0; long nch=1;
    long n=1;

    while (n <= 1){
        std::cout << "Введите n>1: ";
        std::cin >> n;
    }

    while (a <= n) {
            ch = ch + a;
            a = a + 2;
        }
    
            std::cout << "Сумма чётных: " << ch << std::endl;
    while (b<=n) {
            nch = nch * b;
            b = b + 2;
        }
            std::cout << "Произведение нечётных: " << nch << std::endl;

    }
