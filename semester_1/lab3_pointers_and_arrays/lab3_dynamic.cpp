// solve task with usage of
// dymanic arrays
#include <iostream>
#include <random>
#include <limits>
//Печать массива
void printarray (int* Arr,int size){
    for(int i=0;i<size;++i){
        std::cout << Arr[i] << " ";
    }
    std::cout << std::endl;
}
//Ход программы
int main(){
    int size,mode;
    std::cout << "Введите размер массива в элементах:";
    while (!(std::cin >> size) || (size<1)){
        std::cout << "Неправильный ввод. Размер должен быть положительным. Введите размер:";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    int* Arr = new int[size];
    std::cout << "ВВЕДИТЕ: \n 1, если хотите ввести массив вручную \n 0, если хотите автоматически заполнить массив в нужном диапазоне чисел \n ОТВЕТ:";
    while (!(std::cin >> mode) || mode>1 || mode<0) {
        std::cout << "Ошибка ввода, попробуйте снова.\n ВВЕДИТЕ: \n 1, если хотите ввести массив вручную \n 0, если хотите автоматически заполнить массив в нужном диапазоне чисел \n ОТВЕТ:";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //Ручной ввод массива
    if (mode==1){
        std::cout << "Вводите " << size << " элементов:" << std::endl;
        for (int i=0;i<size;++i){
            if (!(std::cin >> Arr[i])){
                std::cout << "Ошибка ввода";
                return 1;
            };
        }
        std::cout << "Исходный массив: ";
        printarray(Arr,size);
    }
    //Автоматический ввод массива
    else if(mode==0){
        int a,b;
        std::cout << "Введите нижнюю границу элементов массива:";
        std::cin >> a;
        std::cout << "Введите вернюю границу элементов массива:";
        std::cin >> b;
        if (a>b){
            std::cout << "a должно быть меньше b";
            exit(404);
        }
        std::mt19937 gen(time(0));
        std::uniform_int_distribution<int> dist(a, b);
        for (int i=0;i<size;i++){
            int x = dist(gen);
            Arr[i] = x;
        }
    }
    //задание 1 DONE
    int max=0;
    for (int i=0;i<size;++i){
        int current=0;
        for (int j=i;j<size;++j){
            bool notunique=false;
            for (int k=i;k<j;++k){
                if (Arr[k]==Arr[j]){
                    notunique=true;
                    break;
                }
            }

            if (notunique==true){
                break;
            }
            current++;
        }
        if (current>max){
            max=current;
        }
    }

    std::cout << "Длина самой длинной цепочки подряд стоящих различных элементов: " << max << std::endl;
    //задание 2 DONE
    int summa=0;
    bool k=false;
    for (int i=0;i<size;++i){
        if (k==false&&Arr[i]==0){
            k=true;
        }
        if (k==true){
            summa+=abs(Arr[i]);
        }
    }
    if (k==true){
    std::cout << "Сумма модулей элементов после первого нулевого: " << summa << std::endl;
    }
    else std::cout << "Сумма модулей элементов после первого нулевого: " << "—" << std::endl;

    //Сжатие массива () - DONE
    std::cout << "Исходный массив: ";
    printarray(Arr,size);
    
    int write = 0;
    for (int read=0; read<size; read+=2) {
        int temp = Arr[read];
        for (int j=read; j>write; j--) Arr[j] = Arr[j-1];
        Arr[write] = temp;
        write++;
    }

    std::cout << "Преобразованный массив: ";
    printarray(Arr,size);
    delete[] Arr;
}