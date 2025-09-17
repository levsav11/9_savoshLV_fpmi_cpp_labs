#include <iostream>
int main() {
    setlocale(LC_ALL, "RUS");
    int a,b,c,n;
    //Ввод и проверка
    std::cout << "Введите n: ";
    while (!(std::cin >> n) || n<1) {
    std::cout << "n должно быть натуральным. Введите n: ";
    std::cin.clear();
    std::cin.ignore(1000, '\n');}

    //По формуле Евклида
    std::cout << "Тройки:" << std::endl;
    for(a=1;a<n;a++){
        for (b=1;b<n;b++){
            for (c=1;c<n;c++){
                if ((c*c==a*a+b*b) && (c>b)&&(b>a)){
                    std::cout << a << " " << b << " " <<  c << std::endl;
                }
            }
        }  
    }     
}