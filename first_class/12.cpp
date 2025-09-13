#include <iostream>
#include <cmath>

int main() {
    setlocale(LC_ALL, "RUS");
    int n;int k;int str=1;int date;

    //Ввод n и проверка
    std::cout << "Введите n - номер дня недели первого числа (от 1 до 7): ";
    while (!(std::cin >> n) || (n < 1)||(n > 7)) {
    std::cout << "n должно быть целым числом от 1 до 7. Введите n: " << std::endl;
    std::cin.clear();
    std::cin.ignore(1000, '\n');}
    date=1-n+1;
    //Ввод k и проверка
    std::cout << "Введите k - количество дней в месяце (от 1 до 99)): ";
    while (!(std::cin >> k) || (k < 1)||(k > 99)) {
    std::cout << "k должно быть целым числом от 1 до 99. Введите k: " << std::endl;
    std::cin.clear();
    std::cin.ignore(1000, '\n');}

    //Ход программы
    while(date<=k){
        std::cout << str << "  |  ";
        for (int i=1;i<=7;i++){
            if(date>0&&date<=k){
                if (date<10){
                    std::cout << " " << date << " ";}
                else{
                    std::cout << date << " ";}
            }
            else{std::cout << "   ";}
            date+=1;
        }
        std::cout << "\n";
        str+=1;
    }
    }