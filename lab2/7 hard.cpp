#include <iostream>
#include <cmath>
int main() {
    setlocale(LC_ALL, "RUS");
    int max;
    //Ввод и проверка
    std::cout << "Введите n: ";
    while (!(std::cin >> max) || max<1) {
    std::cout << "n должно быть натуральным. Введите n: ";
    std::cin.clear();
    std::cin.ignore(1000, '\n');}

    //По формуле Евклида
    std::cout << "Тройки:" << std::endl;
    //Ограничение m и n
    int lim=sqrt(max);
    for(int n=1;n<lim;n++){
        for(int m=2;m<lim;m++){
            if((m>n) && ((m-n)%2==1)){
            if(((m*m)-(n*n)<=max) && (2*m*n<=max) && ((m*m)+(n*n)<=max)){
               std::cout << "a:" << (m*m)-(n*n) << " b:" << (2*m*n) << " c:" << (m*m)+(n*n) << std::endl;
            }}}
    }
}       
