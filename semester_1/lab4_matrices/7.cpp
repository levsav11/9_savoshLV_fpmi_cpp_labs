#include <iostream>
#include <iomanip>
#include <limits>
//Печать строки
void print(std::string str){
    std::cout << str;
}
//Печать int
void printint(int a){
    std::cout << a;
}
//Печать массива
void printArray(int* &A,const int &len){
    for (int i = 0; i < len; i++){
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

int** allocateMatrix(int rows,int cols){
        int** matr = new int*[rows]; 
    for(int i=0; i<cols; i++){
        matr[i] = new int[cols];
    }
    return matr;
}

void deleteMatrix(int** &matr, int rows){
    for (int i=0; i<rows; i++){
        delete[] matr[i];
    }
    delete[] matr;
}

void printMatrix(int** &matr,int rows,int cols,int maxwidth){
    for (int j = 0; j < rows; j++){
        for (int i = 0; i < cols; i++) {
            std::cout << std::setw(maxwidth) << matr[i][j];
        }
        std::cout << "\n";
    }
}

int main(){
    setlocale(LC_ALL,"ru");
    int len, k=1;
    print("Введите длину стороны квадрата матрицы: ");
    while (!(std::cin >> len) || (len < 1)){
        print("Неверный размер массива. Попробуйте ещё раз: ");
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
        for (int i=left;i<=right;++i){
            int j = up;
            Matrix[i][j]=k;
            k++;
            if (k==sq) break;
        }
        up+=1;
        //сверху вниз
        for (int j=up;j<=down;++j){
            int i = right;
            Matrix[i][j]=k;
            k++;
            if (k==sq) break;
        }
        right-=1;
        //справа налево
        for (int i=right;i>=left;--i){
            int j = down;
            Matrix[i][j]=k;
            k++;
            if (k==sq) break;
        }
        down-=1;
        //снизу вверх
        for (int j=down;j>=up;--j){
            int i = left;
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
    for(int i=0;i<len;++i){
            int j=len-1-i;
            summa+=Matrix[i][j];
        }
    print("Сумма элементов побочной диагонали: ");
    printint(summa);

    //Удаление матрицы
    deleteMatrix(Matrix,len);
}