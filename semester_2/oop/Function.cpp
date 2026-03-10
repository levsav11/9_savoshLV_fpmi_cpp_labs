#include "Function.h"
#include <cmath>

double LinearFunction::Evaluate(double x){
    return a * x + b;
}
void LinearFunction::Solve(){
    if (a != 0){
            solutions_.insert( -b / a);
    }
    else if (b == 0){
        throw(std::invalid_argument("Решений бесконечно много"));
    }
    else{
        throw(std::invalid_argument("Решений нет"));
    }
}
void LinearFunction::PrintEquation(){
    std::cout << a << "x + " << b  << " = 0" << std::endl;
}
double QuadraticFunction::Evaluate(double x){
    return a * x * x + b * x + c;
}
void QuadraticFunction::Solve(){
    double D = b * b - 4 * a * c;
    if (D > 0){
        solutions_.insert((-b + sqrt(D)) / (2 * a));
        solutions_.insert((-b - sqrt(D)) / (2 * a));
    }
    else if (D == 0){
        solutions_.insert(-b / (2 * a));
    }
    else{
        throw(std::invalid_argument("Решений нет"));
    }
}
void QuadraticFunction::PrintEquation(){
    std::cout << a << "x^2 + " << b << "x + " << c << " = 0" << std::endl;
}