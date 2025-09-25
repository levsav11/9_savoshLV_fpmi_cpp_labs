#include <iostream>
int main(){
    setlocale(LC_ALL, "RUS");
    int n, a, rev=0;
    //Ввод и проверка
    std::cout << "Введите n: ";
    while (!(std::cin >> n) || n < 1000 || n > 9999) {
    std::cout << "n должно быть больше 4-х значным целым числом. Введите n: " << std::endl;
    std::cin.clear();
    std::cin.ignore(1000, '\n');}
    //Проверка на палиндром
    a=n;
    while (a>0){
        rev=(rev*10)+a%10;
        a/=10;
    }
    if (rev==n){
        std::cout << "Число является палиндромом" << std::endl;
    }
    else{    std::cout <<"Число не является палиндромом" << std::endl;}
}