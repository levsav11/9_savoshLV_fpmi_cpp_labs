#include "Function.h"
int main(){
    int n = 5;
    Function** arr = new Function*[n];
    arr[0]= new LinearFunction(5,2);
    arr[1]= new QuadraticFunction(3,2,1);
    arr[2]= new LinearFunction(18,5);
    arr[3]= new QuadraticFunction(0,2,1);
    arr[4]= new LinearFunction(0,0);
}