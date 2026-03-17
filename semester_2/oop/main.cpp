#include "Function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
template <typename T>
T ReadNumber(std::string&& msg = "Введите число: "){
    T x;
    std::cout << msg;
    while(!(std::cin >> x)) {
        std::cout << "Ошибка ввода. Введите число повторно: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}

bool DoubleEqual(double a, double b, double eps = 1e-9) {
    return std::abs(a - b) < eps;
}

bool LinearSortRule(const Function *f1, const Function *f2){
    return f1->GetB() > f2->GetB();
}

bool QuadraticSortRule(const QuadraticFunction *f1, const QuadraticFunction *f2){
    return f1->GetA() < f2->GetA();
}

void OutputToFile(Function** arr, size_t n, const std::string& filename){
        std::ofstream out(filename);
        for (size_t i = 0; i < n; ++i)
        {
            arr[i] -> PrintEquation(out);
            arr[i] -> Solve(out);
            out << '\n';
        }
}


void printErrorBlue(const std::exception& e, const std::string& context){
    std::cout << "\033[34m" << context << e.what() << "\033[0m" << std::endl;
}

void printMsgPink(const std::string& msg){
    std::cout << "\033[35m" << msg << "\033[0m" << std::endl;
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
    std::cout << "Квадратичных функций: " << quadraticCounter << std::endl;
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
}

void Zad3(Function** arr, size_t n){
    printMsgPink("(3):");
    double x = ReadNumber<double>("Введите x: ");
    double y = ReadNumber<double>("Введите y: ");
    std::cout << "\nУравнения, для которых f(" << x << ") = " << y << ":" << std::endl;
    bool empty = true;
    for (size_t i = 0; i < n; ++i){
        if (DoubleEqual(arr[i] -> Evaluate(x), y)){
            arr[i] -> PrintEquation(std::cout);
            empty = false;
        }
    }
    if (empty){
        std::cout << "нет подходящих уравнений" << std::endl;
    }
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
    delete[] arrLinear;
}

void Zad5(Function** arr, size_t n){
    printMsgPink("(5):");
    QuadraticFunction** arrQuadratic = new QuadraticFunction*[n]{};
    size_t index = 0;
    for (size_t i = 0; i < n; ++i){
        if (QuadraticFunction* curr = dynamic_cast<QuadraticFunction*>(arr[i])){
            if (curr -> IsFullSquare()){
                arrQuadratic[index++] = curr;
            }
        }
    }
    std::sort(arrQuadratic, arrQuadratic + index, QuadraticSortRule);
    std::cout << "Квадратичные функции, которые являются полными квадратами, в порядке возрастания a:" << std::endl;
    bool empty = true;
    for (size_t i = 0; i < index; ++i){
        arrQuadratic[i] -> PrintEquation(std::cout);
        empty = false;
    }
    if (empty){
        std::cout << "нет подходящих уравнений" << std::endl;
    }
    delete[] arrQuadratic;
}

std::pair<Function**, size_t> ReadArrayFromFile(const std::string& filename){
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Файл не может быть открыт");
    }
    if (in.peek() == EOF){
        throw std::runtime_error("Файл пуст");
    }
    std::string line;
    int counter = 0, index = 0;
    while (std::getline(in, line) && !line.empty()){
        ++counter;
    }
    --counter;
    in.clear();
    in.seekg(0, std::ios::beg);
    Function** arr = new Function*[counter]{};
    std::getline(in, line);
     while(std::getline(in, line)){
        std::istringstream iss(line);
        int a, b, c;
        if (!(std::getline(iss, line, ','))){
             throw std::runtime_error("Неверный формат данных в файле");
        }
        else {
            try{
                a = std::stoi(line);
            }
            catch (std::invalid_argument& e){
                printErrorBlue(e, "Ошибка чтения коэффициента a: ошибка ");
                continue;
            }
        }

        if (!(std::getline(iss, line, ','))){
             throw std::runtime_error("Неверный формат данных в файле");
        }
        else {
            try{
                b = std::stoi(line);
            }
            catch (std::invalid_argument& e){
                printErrorBlue(e, "Ошибка чтения коэффициента b: ошибка ");
                continue;
            }
        }
        if (std::getline(iss, line, ',')){
            try{
                c = std::stoi(line);
                arr[index++] = new QuadraticFunction(a,b,c);
            }
            catch(const std::invalid_argument& e){
                printErrorBlue(e, "Ошибка чтения коэффициента c: ошибка ");
                continue;
            }
            catch(const std::logic_error& e){
                printErrorBlue(e, "Ошибка создания квадратичной функции: ");
                continue;
            }
        }
        else{
            try{
                arr[index++] = new LinearFunction(a,b);
            }
            catch(const std::invalid_argument& e){
                printErrorBlue(e, "Ошибка создания линейной функции: ");
            }
        }
    }
    return std::make_pair(arr, index);
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

void Menu(Function** arr, size_t n){
    std::cout << "Выберите запрос:" << std::endl;
    std::cout << "0. Выйти из программы." << std::endl;
    std::cout << "1. Подсчитать количество линейных и квадратичных функций." << std::endl;
    std::cout << "2. Вывести уравнения, не имеющие решений." << std::endl;
    std::cout << "3. Вывести уравнения, для которых f(x) = y при заданных x и y." << std::endl;
    std::cout << "4. Вывести линейные уравнения с коэффициентами b > a в порядке убывания b." << std::endl;
    std::cout << "5. Вывести квадратичные функции, которые являются полными квадратами, в порядке возрастания a." << std::endl;
    int x = ReadNumber<int>("ВВЕДИТЕ номер запроса: ");
    switch (x){
        case 0:
            std::cout << "Выход из программы..." << std::endl;
            break;
        case 1:
            Zad1(arr, n);
            break;
        case 2:
            Zad2(arr, n);
            break;
        case 3:
            Zad3(arr, n);
            break;
        case 4:
            Zad4(arr, n);
            break;
        case 5:
            Zad5(arr, n);
            break;
        default:
            std::cout << "Неверный номер запроса\n" << std::endl;
            Menu(arr, n);
            break;
    }
}

int main(){
    auto [arr, size] = ReadArrayFromFile("input.txt");
    OutputToFile(arr, size, "output.txt");
    Menu(arr, size);
    ClearArray(arr, size);
}