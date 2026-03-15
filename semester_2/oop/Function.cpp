#include "Function.h"
#include <cmath>

size_t Function::counter_ = 0;
bool LinearFunction::IsLinear(){
    return true;
}
bool LinearFunction::IsQuadratic(){
    return false;
}
void LinearFunction::Calculate(){
    if (a_ != 0){
            solutions_.insert( -b_ / a_);
    }
    else if (b_ == 0){
        throw(std::logic_error("Решений бесконечно много"));
    }
    else{
        throw(std::logic_error("Решений нет"));
    }
}
LinearFunction::LinearFunction(double a, double b) 
        :  a_(a), b_(b), index_(++counter_) {}; //ax + b
double LinearFunction::Evaluate(double x){
    return a_ * x + b_;
}
void LinearFunction::Solve(){
        try{
            this->Calculate();
            std::cout << "Решение: " << *solutions_.begin() << std::endl;
        }
        catch(const std::logic_error& e){
            std::cout << e.what() << std::endl;
        }
}
void LinearFunction::PrintEquation(){
    std::cout << a_ << "x + " << b_  << " = 0" << std::endl;
}
size_t LinearFunction::GetNumber(){
    return index_;
}


bool QuadraticFunction::IsLinear(){
    return false;
}
bool QuadraticFunction::IsQuadratic(){
    return true;
}
void QuadraticFunction::Calculate(){
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
QuadraticFunction::QuadraticFunction(double a, double b, double c) 
        : a_(a), b_(b), c_(c), index_(++counter_){
            if (a == 0){
                --counter_;
                throw(std::invalid_argument("многочлен не является квадратным"));
            }
        }; //ax^2 + bx + c
double QuadraticFunction::Evaluate(double x){
    return a_ * x * x + b_ * x + c_;
}
void QuadraticFunction::Solve(){
        try{
            this->Calculate();
            switch (solutions_.size()){
                case 1:
                    std::cout << "Решение: " << *solutions_.begin() << std::endl;
                    break;
                case 2:
                    std::cout << "Решения: " << *solutions_.begin() << " и " 
                    << *(++solutions_.begin()) << std::endl;
                    break;
                default:
                    throw (std::logic_error("Ошибка нахождения решений"));
            }
        }
        catch(const std::logic_error& e){
            std::cout << e.what() << std::endl;
        }
}
void QuadraticFunction::PrintEquation(){
    std::cout << a_ << "x^2 + " << b_ << "x + " << c_ << " = 0" << std::endl;
}
size_t QuadraticFunction::GetNumber(){
    return index_;
}