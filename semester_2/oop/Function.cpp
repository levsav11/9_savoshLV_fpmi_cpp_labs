#include "Function.h"
#include <cmath>

size_t Function::counter_ = 0;
bool LinearFunction::IsLinear() const{
    return true;
}
bool LinearFunction::IsQuadratic() const{
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
double LinearFunction::Evaluate(double x) const{
    return a_ * x + b_;
}
void LinearFunction::Solve(std::ostream& os){
        try{
            this->Calculate();
            os << "Решение: " << *solutions_.begin() << std::endl;
        }
        catch(const std::logic_error& e){
            os << e.what() << std::endl;
        }
}
void LinearFunction::PrintEquation(std::ostream& os) const{
    if (a_ != 1) {
        os << a_;
    }
    os <<"x + " << b_  << " = 0" << std::endl;
}
size_t LinearFunction::GetNumber() const{
    return index_;
}

double LinearFunction::GetA() const{
    return a_;
}
double LinearFunction::GetB() const{
    return b_;
}

bool QuadraticFunction::IsLinear() const{
    return false;
}
bool QuadraticFunction::IsQuadratic() const{
    return true;
}
void QuadraticFunction::Calculate(){
    double D = (b_ * b_) - (4 * a_ * c_);
    if (D > 0){
        solutions_.insert((-b_ + sqrt(D)) / (2 * a_));
        solutions_.insert((-b_ - sqrt(D)) / (2 * a_));
    }
    else if (D == 0){
        solutions_.insert(-b_ / (2 * a_));
    }
    else{
        throw(std::logic_error("Решений нет"));
    }
}
QuadraticFunction::QuadraticFunction(double a, double b, double c) 
        : a_(a), b_(b), c_(c), index_(++counter_){
            if (a == 0){
                --counter_;
                throw(std::logic_error("многочлен не является квадратным"));
            }
        }; //ax^2 + bx + c
double QuadraticFunction::Evaluate(double x) const{
    return a_ * x * x + b_ * x + c_;
}
void QuadraticFunction::Solve(std::ostream& os){
        try{
            this->Calculate();
            switch (solutions_.size()){
                case 1:
                    os << "Решение: " << *solutions_.begin() << std::endl;
                    break;
                case 2:
                    os << "Решения: " << *solutions_.begin() << " и " 
                    << *(++solutions_.begin()) << std::endl;
                    break;
                default:
                    throw (std::logic_error("Ошибка нахождения решений"));
            }
        }
        catch(const std::logic_error& e){
            os << e.what() << std::endl;
        }
}
void QuadraticFunction::PrintEquation(std::ostream& os) const{
    if (a_ != 1){
        os << a_;
    }
    os << "x^2 + ";
    if (b_ != 1){
        os << b_;
    } 
    os << "x + " << c_ << " = 0" << std::endl;
}
size_t QuadraticFunction::GetNumber() const{
    return index_;
}
double QuadraticFunction::GetA() const{
    return a_;
}
double QuadraticFunction::GetB() const{
    return b_;
}
double QuadraticFunction::GetC() const{
    return c_;
}
bool QuadraticFunction::IsFullSquare() const{
    if ((GetB()*GetB() - (4 * GetA() * GetC())) == 0){
        return true;
    }
    return false;
}

