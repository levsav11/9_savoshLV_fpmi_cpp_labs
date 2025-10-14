// solve task with usage of
// dymanic arrays
#include <iostream>
#include <random>
//Печать массива
void printArray(const int* A,const int &size){
    for (int i = 0; i < size; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}
//Печать строки
void print(std::string str){
    std::cout << str;
}
//Ход программы
int main(){
    int size,mode;
    print("Введите размер массива в элементах:");
    while (!(std::cin >> size) || (size<1)){
        print("Неправильный ввод. Размер должен быть положительным. Введите размер:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int* Arr = new int[size];
    print("ВВЕДИТЕ: \n 1, если хотите ввести массив вручную \n 0, если хотите автоматически заполнить массив в нужном диапазоне чисел \n ОТВЕТ:");
    while (!(std::cin >> mode) || mode>1 || mode<0) {
        print("Ошибка ввода, попробуйте снова.\n ВВЕДИТЕ: \n 1, если хотите ввести массив вручную \n 0, если хотите автоматически заполнить массив в нужном диапазоне чисел \n ОТВЕТ:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //Ручной ввод массива
    if (mode==1){
        std::cout << "Вводите " << size << " элементов:" << std::endl;
        for (int i=0;i<size;++i){
            if (!(std::cin >> Arr[i])){
                print("Ошибка ввода");
                return 1;
            };
        }
        print("Исходный массив: ");
        printArray(Arr,size);
    }
    //Автоматический ввод массива
    else if(mode==0){
        int a,b;
        print("Введите НИЖНЮЮ границу элементов массива:");
        while (!(std::cin >> a)){
            print("Неправильный ввод. Введите нижнюю границу элементов массива:");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        print("Введите ВЕРХНЮЮ границу элементов массива:");
        while (!(std::cin >> b)||b<a){
            print("Неправильный ввод. Введите вернюю границу элементов массива (не меньше нижней):");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    print("Исходный массив: ");
    printArray(Arr,size);
    
    int write = 0;
    for (int read=0; read<size; read+=2) {
        int temp = Arr[read];
        for (int j=read; j>write; j--) Arr[j] = Arr[j-1];
        Arr[write] = temp;
        write++;
    }

    print("Преобразованный массив: ");
    printArray(Arr,size);
    delete[] Arr;
}