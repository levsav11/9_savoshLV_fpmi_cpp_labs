#include <iostream>
int main() {
    setlocale(LC_ALL, "RUS");
    long a=0; long b=1; long ch=0; unsigned long nch=1;
    int n=3;
    std::cout << "Введите n: ";
    while (!(std::cin >> n) || n <= 1) {
    std::cout << "n должно быть больше 1 и целым числом. Введите n: ";
    std::cin.clear(); // сброс флагов ошибок
    std::cin.ignore(1000, '\n'); // очистка буфера ввода
}

    while (a <= n) {
            ch = ch + a;
            a = a + 2;}
            std::cout << "Сумма чётных: " << ch << std::endl;
    while (b<=n) {
            nch = nch * b;
            b = b + 2;}
            std::cout << "Произведение нечётных: " << nch << std::endl;
    }
