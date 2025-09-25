#include <iostream>
#include <numeric>
#include <cmath>
int main() {
    setlocale(LC_ALL, "RUS");
    int a,b,c,n,count=0;
    //Ввод и проверка
    std::cout << "Введите n: ";
    while (!(std::cin >> n) || n<1) {
        std::cout << "n должно быть натуральным. Введите n: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //По формуле Евклида
    std::cout << "Тройки:" << std::endl;
    for(a = 1;a <= n;a++){
        for (b = 1;b <= n;b++){
            int sq = a * a + b * b;
            int c = static_cast<int>(sqrt(sq));
            if ((c * c == sq)&&(c <= n)&&(b < c)&&(a < b)){
                    std::cout << a << " " << b << " " <<  c << std::endl;
                    count+=1;
                }
        }  
    }     
    std::cout << "Всего троек:" << count << std::endl;
}