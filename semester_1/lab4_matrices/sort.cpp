#include <iostream>
#include <random>
#include <iomanip>
#include <limits>
void swap (int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
void mirrorArray(int* &arr, int size){
  for (int i = 0;i < (size / 2); ++i){
    swap(arr[i],arr[size - i - 1]);
  }
}
void printStr(std::string str){
    std::cout << str;
}
void printInt(int a){
    std::cout << a;
}
void printArray(int* A,const int &len){
    for (int i = 0; i < len; i++){
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}
void allocateMatrix(int**& matr,int rows,int cols){
     matr = new int*[rows]; 
    for(int i=0; i < rows; i++){
        matr[i] = new int[cols];
    }
  //  return matr;
}
void deleteMatrix(int**& matr,int rows){
    for (int i = 0; i < rows; i++){
        delete[] matr[i];
    }
    delete[] matr;
}
void printMatrix(int** &matr,int &rows,int &cols,int maxwidth){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(maxwidth) << matr[i][j];
        }
        std::cout << "\n";
    }
}
void fillMatrixFromKeyboard(int** matrix, int rows, int cols) {
  std::cout << "Введите элементы матрицы:" << std::endl;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << "Элемент [" << i << "][" << j << "]: ";
      std::cin >> matrix[i][j];
    }
  }
}
void fillMatrixRandom(int** &matrix, int rows, int cols, int limit1, int limit2) {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> dist(limit1, limit2);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix[i][j] = dist(gen);
    }
  }
}

//сортировки массивов

void sortBubble(int* &arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortCounting(int* &arr, int size) {
  int min = arr[0];
  int max = arr[0];
  for (int i = 0;i < size - 1; ++i){
    if (arr[i+1]>max) {
      max = arr[i+1];
    }
    if (arr[i+1]<min) {
      min = arr[i+1];
    }
  }

  int newSize = max - min + 1;
  int* count = new int[newSize] {};

  for (int j = 0; j < size; ++j) {
    count[arr[j] - min]++;
  }
  
  int index = 0;
  for (int num = 0; num < newSize; ++num) {
      int value = num + min;
      for (int i = 0; i < count[num]; ++i) {
          arr[index] = value;
          index++;
      }
  }

  delete[] count;
}

void sortInsertion(int* &arr, int size) {
    for (int i = 1; i < size; ++i) {
        int currentValue = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > currentValue) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = currentValue;
    }
}

void sortMerge(int* &arr, int size) {
    int mid = size / 2;
    int* left = new int[mid];
    int* right = new int[size - mid];
    
    for (int i = 0; i < mid; i++)
        left[i] = arr[i];
    for (int i = 0; i < size - mid; i++)
        right[i] = arr[mid + i];
    
    sortMerge(left, mid);
    sortMerge(right, size - mid);

    int i = 0, j = 0, index = 0;
    while (i < mid && j < size - mid) {
        if (left[i] <= right[j]) {
            arr[index++] = left[i++];
        } else {
            arr[index++] = right[j++];
        }
    }
    
    while (i < mid) arr[index++] = left[i++];
    while (j < size - mid) arr[index++] = right[j++];
}

void sortSelection(int* &arr, int size) {
  int* newArr = new int[size];
  for (int i = 0; i < size; ++i){
    int min = arr[0];
    for (int j = 1; j < size; ++j){
      if (arr[j] < min){
        min = arr[j];
      }
    }
    newArr[i] = min;
    arr[i] = std::numeric_limits<int>::max();
  }

  for (int i = 0; i < size; ++i){
    arr[i] = newArr[i];
  }
  delete[] newArr;
}

void sortQuick(int* &arr, int size) {
    int pivot = arr[rand() % size];
    int left = 0, right = size - 1;
    
    while (left <= right) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;
        if (left <= right) {
          swap(arr[left++], arr[right--]);
        }
    }
    int* leftArr = arr;
    int* rightArr = arr + left;
    
if (right + 1 > 0) sortQuick(leftArr, right + 1);
if (size - left > 0) sortQuick(rightArr, size - left);
}

//Выполнить функцию для массива как функцию для матрицы по рядам
void doWithMatrix(void (*function)(int* &arr,int size),int** &matrix,int rows,int cols){
  for (int i = 0;i<rows;++i){
    function(matrix[i],cols);
  }
}

int main(){
    setlocale(LC_ALL,"Rus");
    //Выбор режима ввода
    int mode;
    printStr("ВВЕДИТЕ: \n 1, если хотите ввести матрицу вручную \n 2, если хотите автоматически заполнить матрицу в нужном диапазоне чисел \n ОТВЕТ:");
    while (!(std::cin >> mode) || mode>2 || mode<1) {
        printStr("Ошибка ввода, попробуйте снова.\n ВВЕДИТЕ: \n 1, если хотите ввести матрицу вручную \n 2, если хотите автоматически заполнить матрицу в нужном диапазоне чисел \n ОТВЕТ:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //Выбор типа сортировки
    int sort;
    printStr("ВВЕДИТЕ: \n 1 для пузырьковой сортировки \n 2 для сортировки подсчётом \n 3 для сортировки вставками \n 4 для сортировки слиянием \n 5 для сортировки выбором \n 6 для быстрой сортировки \n ОТВЕТ:");
    while (!(std::cin >> sort) || sort>8 || sort<1) {
        printStr("Ошибка ввода, попробуйте снова.\n ВВЕДИТЕ: \n 1 для пузырьковой сортировки \n 2 для сортировки подсчётом \n 3 для сортировки вставками \n 4 для сортировки слиянием \n 5 для сортировки выбором \n 6 для быстрой сортировки \n ОТВЕТ:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int order;
    printStr ("Выберите, хотите ли получить ввод по возрастанию (1) или по убыванию (2):");
    while (!(std::cin >> order) || (order < 1) || (order > 2)){
        printStr("Неправильный ввод. Выберите, хотите ли получить ввод по возрастанию (1) или по убыванию (2):");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //Ввод матрицы
    int length,width;
    printStr ("Введите длину матрицы:");
    while (!(std::cin >> length) || (length<=1)){
        printStr("Неправильный ввод. Введите длину матрицы (Натуральное число > 1):");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    printStr ("Введите ширину матрицы:");
    while (!(std::cin >> width)){
        printStr("Неправильный ввод. Введите длину матрицы:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int** matrix;
    allocateMatrix(matrix,length,width);
    if (mode==1){
        fillMatrixFromKeyboard(matrix,length,width);
    }
    else {
        int limit1,limit2;
        printStr ("Введите целочисленную нижнюю границу чисел, которые будут в матрице:");
        while (!(std::cin >> limit1)){
            printStr("Введите нижнюю границу чисел, которые будут в матрице:");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        printStr ("Введите целочисленную верхнюю границу чисел, которые будут в матрице:");
        while (!(std::cin >> limit2)||(limit2<=limit1)){
            printStr("Введите верхнюю границу чисел, которые будут в матрице (верхняя должна быть выше нижней):");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        fillMatrixRandom(matrix,length,width,limit1,limit2);
    }
    printStr("Исходная матрица: \n");
    printMatrix(matrix,length,width,5);
    printStr("\n");

    //Сортировка
    if (sort == 1){
      doWithMatrix(sortBubble, matrix, length, width);
    }
    if (sort == 2){
      doWithMatrix(sortCounting, matrix, length, width);
    }
    if (sort == 3){
      doWithMatrix(sortInsertion, matrix, length, width);
    }
    if (sort == 4){
      doWithMatrix(sortMerge, matrix, length, width);
    }
    if (sort == 5){
      doWithMatrix(sortSelection, matrix, length, width);
    }
    if (sort == 6){
      doWithMatrix(sortQuick, matrix, length, width);
    }

    if (order == 2){
      doWithMatrix(mirrorArray, matrix, length, width);
    }
    //Вывод
    printStr("Итоговая матрица: \n");
    printMatrix(matrix,length,width,5);
}