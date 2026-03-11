#include "Function.h"
#include <cmath>

size_t Function::counter_ = 0;
LinearFunction::LinearFunction(double a, double b) 
        : a_(a), b_(b), index_(counter_++) {}; //ax + b
double LinearFunction::Evaluate(double x){
    return a_ * x + b_;
}
void LinearFunction::Solve(){
    if (a_ != 0){
            solutions_.insert( -b_ / a_);
    }
    else if (b_ == 0){
        throw(std::invalid_argument("Решений бесконечно много"));
    }
    else{
        throw(std::invalid_argument("Решений нет"));
    }
}
void LinearFunction::PrintEquation(){
    std::cout << a_ << "x + " << b_  << " = 0" << std::endl;
}
QuadraticFunction::QuadraticFunction(double a, double b, double c) 
        : a_(a),b_(b), c_(c), index_(counter_++){
            if (a == 0){
                throw(std::invalid_argument("Неверное уравнение"));
            }
        }; //ax^2 + bx + c
double QuadraticFunction::Evaluate(double x){
    return a_ * x * x + b_ * x + c_;
}
void QuadraticFunction::Solve(){
    double D = b_ * b_ - 4 * a_ * c_;
    if (D > 0){
        solutions_.insert((-b_ + sqrt(D)) / (2 * a_));
        solutions_.insert((-b_ - sqrt(D)) / (2 * a_));
    }
    else if (D == 0){
        solutions_.insert(-b_ / (2 * a_));
    }
    else{
        throw(std::invalid_argument("Решений нет"));
    }
}
void QuadraticFunction::PrintEquation(){
    std::cout << a_ << "x^2 + " << b_ << "x + " << c_ << " = 0" << std::endl;
}