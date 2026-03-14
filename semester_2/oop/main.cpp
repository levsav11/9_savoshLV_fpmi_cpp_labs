#include "Function.h"
#include <iostream>
#include <fstream>
void printErrorBlue(const std::invalid_argument& e, const std::string& context){
    std::cout << "\033[34m" << context << e.what() << "\033[0m" << std::endl;
}
int main(){

    int n = 5;
    Function** arr = new Function*[n]{};


        arr[0] = new LinearFunction(5,2);
        arr[1] = new QuadraticFunction(3,2,6);
        arr[2] = new LinearFunction(18,5);
        try{
            arr[3] = new QuadraticFunction(0,2,1);
        }
        catch(const std::invalid_argument& e){
            printErrorBlue(e, "Ошибка создания квадратичной функции: ");
        }
        arr[3] = new QuadraticFunction(1,2,1);
        arr[4] = new LinearFunction(0,0);
        //добавление новых тут

        std::ofstream out("output.txt");
        
    


    for(int i = 0; i < n; ++i){
    delete arr[i];
    }
    delete[] arr;
}