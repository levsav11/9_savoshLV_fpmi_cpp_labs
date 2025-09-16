#include <iostream>
#include <cmath>
int main() {
    setlocale(LC_ALL, "RUS");
    int n;long a; unsigned long long s=0;
    //Ввод и проверка
    std::cout << "Введите n: ";
    while (!(std::cin >> n) || n <= 0) {
    std::cout << "n должно быть больше 0 и целым числом. Введите n: " << std::endl;
    std::cin.clear();
    std::cin.ignore(1000, '\n');}

    while (a<=n){
        s+=pow(a,a);
        a+=1;
    }
    std::cout << "Ответ:" << s;
    return 0;
}