#include <iostream>
int main() {
    setlocale(LC_ALL, "RUS");
    int k;long a; unsigned long f=1;
    //Ввод и проверка
    std::cout << "Введите k: ";
    while (!(std::cin >> k) || k <= 0) {
    std::cout << "k должно быть больше 0 и целым числом. Введите k: " << std::endl;
    std::cin.clear();
    std::cin.ignore(1000, '\n');}

    if (k%2==0){
        a=2;
    }
    else{
        a=1;
    }

    while (a<=k){
        f*=a;
        a+=2;
    }
    std::cout << "Двойной факториал k равен: " << f;
    return 0;
}