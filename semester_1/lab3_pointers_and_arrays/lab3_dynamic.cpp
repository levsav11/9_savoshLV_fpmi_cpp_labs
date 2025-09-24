// solve task with usage of
// dymanic arrays
#include <iostream>
#include <random>

//Ввод и проверка. n - вводимая переменная, a,b - условия повторного ввода ((!cin И a) ИЛИ b)
auto inputcheck(auto n, bool a,bool b,bool c, std::string term){
std::cout << "Введите " << n << "("<< term << "):";
while ((!(std::cin >> n) & a) || b){
    std::cout << "Неправильный ввод. Введите " << n << "("<< term << "):";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}
return n;
}
int main(){
    int n;
    inputcheck(n,n<0,)
}