#include "Function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
double ReadDouble(std::string&& msg = "Введите число: "){
    double x;
    std::cout << msg;
    while(!(std::cin >> x)) {
        std::cout << "Ошибка ввода. Введите число: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}

bool LinearSortRule(const Function *f1, const Function *f2){
    return f1->GetB() > f2->GetB();
}

void OutputInFile(Function** arr, size_t n, const std::string& filename){
        std::ofstream out(filename);
        for (size_t i = 0; i < n; ++i)
        {
            arr[i] -> PrintEquation(out);
            arr[i] -> Solve(out);
            out << '\n';
        }
}


void printErrorBlue(const std::invalid_argument& e, const std::string& context){
    std::cout << "\033[34m" << context << e.what() << "\033[0m" << std::endl;
}

void printMsgPink(const std::string& msg){
    std::cout << "\033[35m" << msg << "\033[0m" << std::endl;
}

Function** AllocateArray(size_t n){
    Function** arr = new Function*[n]{};
    
    arr[0] = new LinearFunction(5,2);
    arr[1] = new QuadraticFunction(1,5,6);
    arr[2] = new LinearFunction(18,5);
    try{
        arr[3] = new QuadraticFunction(0,2,1);
    }
    catch(const std::invalid_argument& e){
        printErrorBlue(e, "Ошибка создания квадратичной функции: ");
    }
    arr[3] = new QuadraticFunction(1,2,1);
    arr[4] = new LinearFunction(0,0);
    arr[5] = new LinearFunction(1,4);
    //добавление новых тут
    return arr;
}

void ClearArray(Function** arr, size_t n){
    for (size_t i = 0; i < n; ++i)
    {
        delete arr[i];
    }
    delete[] arr;
}

void Zad1(Function** arr, size_t n){
    printMsgPink("(1):");
    size_t linearCounter = 0;
    size_t quadraticCounter = 0;
    for (size_t i = 0; i < n; ++i){
        if (arr[i] -> IsLinear()){
            ++linearCounter;
        }
        else if (arr[i] -> IsQuadratic()){
            ++quadraticCounter;
        } 
    }
    std::cout << "Линейных функций: " << linearCounter << std::endl;
    std::cout << "Квадратичных функций: " << quadraticCounter << std::endl << std::endl;
}

void Zad2(Function** arr, size_t n){
    printMsgPink("(2):");
    std::cout << "Уравнения без решений: " << std::endl;
    bool empty = true;
    for (size_t i = 0; i < n; ++i){
        try{
            arr[i]->Calculate();
        }
        catch (const std::logic_error& e){
            std::string msg = e.what();
            if (msg == "Решений нет"){
                arr[i] -> PrintEquation(std::cout);
                empty = false;
            }
        }
    }
    if (empty){
        std::cout << "нет подходящих уравнений" << std::endl;
    }
    std::cout << std::endl;
}

void Zad3(Function** arr, size_t n){
    printMsgPink("(3):");
    double x = ReadDouble("Введите x: ");
    double y = ReadDouble("Введите y: ");
    std::cout << "\nУравнения, для которых f(" << x << ") = " << y << ":" << std::endl;
    bool empty = true;
    for (size_t i = 0; i < n; ++i){
        if (arr[i] -> Evaluate(x) == y){
            arr[i] -> PrintEquation(std::cout);
            empty = false;
        }
    }
    if (empty){
        std::cout << "нет подходящих уравнений" << std::endl;
    }
    std::cout << std::endl;
}
void Zad4(Function** arr, size_t n){
    printMsgPink("(4):");
    std::cout << "Линейные уравнения с коэффициентами b > a в порядке убывания b:" << std::endl;
    Function** arrLinear = new Function*[n]{};
    size_t index = 0;
    for (size_t i = 0; i < n; ++i){
        if ((arr[i] -> IsLinear() == true) && (arr[i] -> GetB() > arr[i] -> GetA())){
            arrLinear[index++] = arr[i];
        }
    }
    std::sort(arrLinear, arrLinear + index, LinearSortRule);
    bool empty = true;
    for (size_t i = 0; i < index; ++i){
        arrLinear[i] -> PrintEquation(std::cout);
        empty = false;
    }
    if (empty){
        std::cout << "нет подходящих уравнений" << std::endl;
    }
    std::cout << std::endl;
    delete[] arrLinear;
}

void Zad5(Function** arr, size_t n){
    printMsgPink("(5):");
    std
}

int main(){
    const size_t size = 6;
    Function** arr = AllocateArray(size);
    OutputInFile(arr, size, "output.txt");
    Zad1(arr, size);
    Zad2(arr, size);
    Zad3(arr, size);
    Zad4(arr, size);
    ClearArray(arr, size);
}