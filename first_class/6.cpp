#include <iostream>
int main(){
    setlocale(LC_ALL, "RUS");
    int n;int a=1;long s=0;
    //Ввод и проверка
    std::cout << "Введите n: ";
    while (!(std::cin >> n) || n <= 0) {
    std::cout << "n должно быть больше 0 и целым числом. Введите n: " << std::endl;
    std::cin.clear();
    std::cin.ignore(1000, '\n');}
    //Так как сумма первых n нечетных чисел равна квадрату n
    std::cout << "Сумма первых n нечётных чисел: " << (n*n);}