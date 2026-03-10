#pragma once
#include <iostream>
#include <unordered_set>

class Function{
    public:
        virtual double Evaluate(double x) = 0;
        virtual void Solve() = 0;
        virtual void PrintEquation() = 0;
    protected:
        std::unordered_set<double> solutions_;
        static size_t counter_;
};

class LinearFunction : public Function{
    private:
        const size_t index;
        double a,b;
    public:
        LinearFunction(double a, double b) 
        : a(a), b(b), index(counter_++) {}; //ax + b
        double Evaluate(double x) override;
        void Solve() override;
        void PrintEquation() override;
};

class QuadraticFunction : public Function{
    private:
        const size_t index;
        double a,b,c;
    public:
        QuadraticFunction(double a, double b, double c) 
        : b(b), c(c), index(counter_++){
            if (a == 0){
                throw(std::invalid_argument("Неверное уравнение"));
            }
        }; //ax^2 + bx + c
        double Evaluate(double x) override;
        void Solve() override;
        void PrintEquation() override;
};

