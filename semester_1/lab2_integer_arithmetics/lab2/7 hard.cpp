#include <iostream>
#include <cmath>
#include <numeric>

int main() {
    setlocale(LC_ALL, "RUS");
    int max; 
    int count = 0;

    std::cout << "Введите n: ";
    while (!(std::cin >> max) || max < 1) {
        std::cout << "n должно быть натуральным. Введите n: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Тройки:" << std::endl;

    for (int m = 2; m * m <= max; m++) {
        for (int n = 1; n < m; n++) {
            if ((m - n) % 2 == 1 && std::gcd(m, n) == 1) { //Примитивные
                int a = m * m - n * n;
                int b = 2 * m * n;
                int c = m * m + n * n;

                //Генерация кратных
                int k = 1;
                while (k * a <= max && k * b <= max && k * c <= max) {
                    std::cout << "a:" << k * a << " b:" << k * b << " c:" << k * c << std::endl;
                    count++;
                    k++;
                }
            }
        }
    }

    std::cout << "Всего троек: " << count << std::endl;
    return 0;
}
