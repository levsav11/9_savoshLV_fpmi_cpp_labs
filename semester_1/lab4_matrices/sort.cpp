#include <iostream>
#include <random>
#include <iomanip>

void printstr(std::string str){
    std::cout << str;
}

void printint(int a){
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
    for(int i=0; i < cols; i++){
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

void sortRowsBubble(int** matrix, int rows, int cols) {
  for (int i = 0; i < rows; i += 1) {
    for (int k = 0; k < cols - 1; k++) {
      for (int j = 0; j < cols - k - 1; j++) {
        if (matrix[i][j] > matrix[i][j + 1]) {
          int tmp = matrix[i][j];
          matrix[i][j] = matrix[i][j + 1];
          matrix[i][j + 1] = tmp;
        }
      }
    }
  }
}

void fillMatrixRandom(int** matrix, int rows, int cols, int limit1, int limit2) {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> dist(limit1, limit2);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = dist(gen);
    }
  }
}

int main(){
    setlocale(LC_ALL,"Rus");
    //Выбор режима ввода
    int mode;
    printstr("ВВЕДИТЕ: \n 1, если хотите ввести матрицу вручную \n 0, если хотите автоматически заполнить матрицу в нужном диапазоне чисел \n ОТВЕТ:");
    while (!(std::cin >> mode) || mode>1 || mode<0) {
        printstr("Ошибка ввода, попробуйте снова.\n ВВЕДИТЕ: \n 1, если хотите ввести матрицу вручную \n 0, если хотите автоматически заполнить матрицу в нужном диапазоне чисел \n ОТВЕТ:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //Выбор типа сортировки
    int sort;
    printstr("ВВЕДИТЕ: \n 1 для пузырьковой сортировки \n 2 для шейкерной сортировки \n 3 для чётно-нечётной сортировки \n 4 для сортировки вставками \n 5 для сортировки выбором \n 6 для сортировки подсчётом \n 7 для сортировки слиянием \n 8 для быстрой сортировки \n ОТВЕТ:");
    while (!(std::cin >> sort) || sort>8 || sort<1) {
        printstr("Ошибка ввода, попробуйте снова.\n ВВЕДИТЕ: \n 1 для пузырьковой сортировки \n 2 для шейкерной сортировки \n 3 для чётно-нечётной сортировки \n 4 для сортировки вставками \n 5 для сортировки выбором \n 6 для сортировки подсчётом \n 7 для сортировки слиянием \n 8 для быстрой сортировки \n ОТВЕТ:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    //Ввод матрицы
    int length,width;
    printstr ("Введите длину матрицы:");
    while (!(std::cin >> length)){
        printstr("Неправильный ввод. Введите длину матрицы:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    printstr ("Введите ширину матрицы:");
    while (!(std::cin >> width)){
        printstr("Неправильный ввод. Введите длину матрицы:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int** matrix = {};
    allocateMatrix(matrix,length,width);
    if (mode==1){
        fillMatrixFromKeyboard(matrix,length,width);
    }
    else {
        int limit1,limit2;
        printstr ("Введите целочисленную нижнюю границу чисел, которые будут в матрице:");
        while (!(std::cin >> limit1)){
            printstr("Введите нижнюю границу чисел, которые будут в матрице:");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        printstr ("Введите целочисленную верхнюю границу чисел, которые будут в матрице:");
        while (!(std::cin >> limit2)||(limit2<=limit1)){
            printstr("Введите верхнюю границу чисел, которые будут в матрице (верхняя должна быть выше нижней):");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        fillMatrixRandom(matrix,length,width,limit1,limit2);
    }
    printstr("Исходная матрица: \n");
    printMatrix(matrix,length,width,5);
    printstr("\n");

    //Сортировка
    //Пузырьковая
    if (sort==1){
        sortRowsBubble(matrix,length,width);
    }

    //Вывод
    printstr("Итоговая матрица: \n");
    printMatrix(matrix,length,width,5);
}