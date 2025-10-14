#include <iostream>
#include <iomanip>
#include <limits>
//Печать
void print(std::string str){
    std::cout << str;
}
//Печать массива
void printArray(int* A,const int &len){
    for (int i = 0; i < len; i++){
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

std::string spaces(const int &count){
    std::string spaces="";
    for (int i=1;i<=count;i++){
        spaces += " ";
    }
    return spaces;
}

void printMatrix(int** M,const int &rows, const int &cols,int maxwidth){
    for (int j = 0; j < cols; j++){
        for (int i = 0; i < rows; i++){
            std::cout << M[i][j] << spaces(maxwidth-std::to_string(M[i][j]).length());
        }
        std::cout << std::endl;
    }
}

int main(){
    int len, k=1;
    print("Введите длину стороны квадрата матрицы:");
    while (!(std::cin >> len) || (len < 1)){
        print("Неверный размер массива:");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    //Создание матрицы
    int** Matrix = new int*[len]; 
    for(int i=0;i<len;i++){
        Matrix[i] = new int[len];
    }
    //Ход
    int left=0,right=len-1,up=0,down=len-1,sq=len*len;
    int maxwidth=std::to_string(sq).length()+2;
    while (k<sq){
        //слева направо
        for (int i=left;i<=right;++i){
            int j = up;
            Matrix[i][j]=k;
            k++;
            if (k==len) break;
        }
        //сверху вниз
        for (int j=up;j<=down;++j){
            int i = right;
            Matrix[i][j]=k;
            k++;
            if (k==len) break;
        }
        //справа налево
        for (int i=right;i>=left;--i){
            int j = down;
            Matrix[i][j]=k;
            k++;
            if (k==len) break;
        }
        //снизу вверх
        for (int j=down;j>up;--j){
            int i = left;
            Matrix[i][j]=k;
            k++;
        }
        up+=1;
        down-=1;
        left+=1;
        right-=1;
    }
    //Печать матрицы
    printMatrix(Matrix, len, len, maxwidth);
    //Удаление матрицы
    for (int i = 0; i < len; ++i){
        delete[] Matrix[i];
    }
    delete[] Matrix;
}