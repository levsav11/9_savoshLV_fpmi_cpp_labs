
// solve task with usage of
// static arrays
#include <iostream>
#include <random>
int mode,size;
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
    std::cin >> size;
    double A[size];
    //режим ввода 1
    if (mode==1){
        std::cout << "Вводите массив:";
        for (int i=0;i<size;i++){
            std::cin >> A[i];
        }
        printArray(A,size);
    }
    //режим ввода 2
    else{
        int a,b,x;
        std::cout << "Введите нижнюю границу элементов массива:";
        std::cin >> a;
        std::cout << "Введите вернюю границу элементов массива:";
        std::cin >> b;
        std::mt19937 gen(798465312);
        std::uniform_real_distribution<double> dist(a, b);
        for (int i=0;i<size;i++){
        double x = dist(gen);
        A[i] = x;
        }
        printArray(A,size);
        }
    //Ход программы
    //Кол-во различных элементов
    int r=size;
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            if ((A[i]!=A[j])&&(i!=j)){
                r-=r;
            }
        }
    }
    std::cout << "Количество различных элементов:" << r << std::endl;
    //Сумма элементов между первым и вторым положительным
    int n1=-1,n2=-1,s=0;
    for (int i=0;i<size;i++){
        if (A[i]>0){
            if (n1=-1){
            n1=i;
            }
            else if (n2=-1){
            n2=i;
            }
            else break;
        }
    }
    for (int i=n1+1;i<n2-1;i++){
        s+=A[i];
    }
    std::cout << "Сумма элементов между первым и вторым положительным:" << s << std::endl;
    //Преобразование
    double lim1,lim2;
    std::cout <<  "Введите НИЖНЮЮ границу интервала, принадлежащие которому элементы будут перенесены в конец:";
    std::cin >> lim1;
    std::cout <<  "Введите ВЕРХНЮЮ границу интервала, принадлежащие которому элементы будут перенесены в конец:";
    std::cin >> lim2;
    
    std::cout << "Исходный массив: ";
    printArray(A, size);
    int writePos = 0;
    for (int i = 0; i < size; i++) {
        if (A[i] <= lim1 || A[i] >= lim2) {
            double temp = A[i];
            for (int j = i; j > writePos; j--) {
                A[j] = A[j - 1];
            }
            A[writePos] = temp;
            writePos++;
        }
    }
    //Вывод
    std::cout << "Полученный массив: ";
    printArray(A,size);
    return 0;
}