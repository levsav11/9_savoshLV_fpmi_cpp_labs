
// solve task with usage of
// static arrays
#include <iostream>
#include <random>
#include <time.h>
int mode,size;

//Ввод и проверка. n - вводимая переменная, a,b - условия повторного ввода ((!cin И a) ИЛИ b)
void inputcheck(auto n, bool a,bool b,bool c, std::string term){
    std::cout << "Введите " << n << "("<< term << "):";
    while ((!(std::cin >> n) & a) || b){
        std::cout << "Неправильный ввод. Введите " << n << "("<< term << "):";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    }

void printArray(double A[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}
int main(){
    //Ввод и проверка
    std::cout << "Введите: \n 1, если хотите ввести массив вручную \n 0, если хотите автоматически заполнить массив в нужном диапазоне чисел \n ОТВЕТ:";
    while (!(std::cin >> mode) || (mode>1) || (mode<0)){
        std::cout << "Неправильный ввод. Введите: \n 1, если хотите ввести массив вручную \n 0, если хотите автоматически заполнить массив в нужном диапазоне чисел \n ОТВЕТ:";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    //Начало
    std::cout << "Введите размер массива в элементах:";
    while (!(std::cin >> size) || (size<1)){
        std::cout << "Неправильный ввод. Размер должен быть положительным. Введите размер:";
        std::cin.clear();
        std::cin.ignore(1000, '\n');}
    double A[size];
    //режим ввода 1
    if (mode==1){
        std::cout << "Вводите массив:";
        for (int i=0;i<size;i++){
            std::cin >> A[i];
        }
        std::cout << "Исходный массив: ";
        printArray(A,size);
    }
    //режим ввода 2
    else{
        int a,b,x;
        std::cout << "Введите НИЖНЮЮ границу элементов массива:";
        if (!(std::cin >> a)){
            exit(0);
        }
        std::cout << "Введите ВЕРХНЮЮ границу элементов массива:";
        if (!(std::cin >> b)){
            exit(0);
        }
        std::mt19937 gen(time(0));
        std::uniform_real_distribution<double> dist(a, b);
        for (int i=0;i<size;i++){
        double x = dist(gen);
        A[i] = x;
        }
        std::cout << "Исходный массив: ";
        printArray(A,size);
        }
    //Ход программы
    //Задание 1 - Кол-во различных элементов DONE
    int count=0;
    for (int i=0; i<size; i++){
        bool isunique = true;
        for (int j=0; j<i; j++){
            if (A[i]==A[j]){
                isunique=false;
                break;
            }
        } 
        if (isunique){
            count++;
        }
    }
    std::cout << "Количество различных элементов: " << count << std::endl;

    //Задание 2 - Сумма элементов между первым и вторым положительным DONE
    int n1=-1,n2=-1,s=0;
    for (int i=0;i<size;i++){
        if (A[i]>0){
            if (n1==-1){
            n1=i;
            std::cout << "Индекс первого положительного числа:" << n1 << std::endl;
            }
            else if (n2==-1){
            n2=i;
            std::cout << "Индекс второго положительного числа:" << n2 << std::endl;
            }
            else if (n2!=-1 && n1!=-1) break;
        }
    }
    if (n1+1==n2){
        std::cout << "Сумма элементов между первым и вторым положительным: " << "—" << std::endl;
    }
    else{
        for (int i=n1+1;i<n2;i++){
            s+=A[i];
        }
        std::cout << "Сумма элементов между первым и вторым положительным:" << s << std::endl;
    }
    
    //Преобразование - доделать
    double lim1,lim2;
    std::cout <<  "Введите НИЖНЮЮ границу интервала, принадлежащие которому элементы будут перенесены в конец:";
    std::cin >> lim1;
    std::cout <<  "Введите ВЕРХНЮЮ границу интервала, принадлежащие которому элементы будут перенесены в конец:";
    std::cin >> lim2;
    int writepos = 0;
    for (int i = 0; i < size; i++) {
        if (A[i] < lim1 || A[i] > lim2) {
            double tmp = A[i];
            for (int j = i; j > writepos; j--) {
                A[j] = A[j - 1];
            }
            A[writepos] = tmp;
            writepos++;
        }
    }
    //Вывод
    std::cout << "Полученный массив: ";
    printArray(A,size);
    return 0;
}