#include <iostream>
#include <iomanip>
#include <limits>
void printstr(std::string str){
    std::cout << str;
}

void printint(int a){
    std::cout << a;
}

void printArray(int* &A,const int &len){
    for (int i = 0; i < len; i++){
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

int** allocateMatrix(int rows,int cols){
        int** matr = new int*[rows]; 
    for(int i=0; i<rows; i++){
        matr[i] = new int[cols];
    }
    return matr;
}

void deleteMatrix(int** &matr,int rows){
    for (int i=0; i<rows; i++){
        delete[] matr[i];
    }
    delete[] matr;
}

void printMatrix(int** &matr,int rows,int cols,int maxwidth){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(maxwidth) << matr[i][j];
        }
        std::cout << "\n";
    }
}

int main(){
    setlocale(LC_ALL,"ru");
    int len, k=1;
    printstr("Введите длину стороны квадрата матрицы: ");
    while (!(std::cin >> len) || (len < 1)){
        printstr("Неверный размер массива. Попробуйте ещё раз: ");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    //Создание матрицы
    int** Matrix = allocateMatrix(len,len);
    //Ход
    int left=0,right=len-1,up=0,down=len-1,sq=len*len;
    int maxwidth=std::to_string(sq).length()+2;
    while (k<=sq){
        //слева направо
        for (int j=left;j<=right;++j){
            int i = up;
            Matrix[i][j]=k;
            k++;
            if (k==sq) break;
        }
        up+=1;
        //сверху вниз
        for (int i=up;i<=down;++i){
            int j = right;
            Matrix[i][j]=k;
            k++;
            if (k==sq) break;
        }
        right-=1;
        //справа налево
        for (int j=right;j>=left;--j){
            int i = down;
            Matrix[i][j]=k;
            k++;
            if (k==sq) break;
        }
        down-=1;
        //снизу вверх
        for (int i=down;i>=up;--i){
            int j = left;
            Matrix[i][j]=k;
            k++;
            if (k==sq) break;
        }
        left+=1;
    }
    //Печать матрицы
    printMatrix(Matrix, len, len, maxwidth);

    //Вычисление суммы элементов побочной диагонали
    int summa=0;
    for(int j=0;j<len;++j){
            int i=len-1-j;
            summa+=Matrix[i][j];
        }
    printstr("Сумма элементов побочной диагонали: ");
    printint(summa);

    //Удаление матрицы
    deleteMatrix(Matrix,len);
}