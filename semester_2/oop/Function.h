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
        const size_t index_;
        double a_,b_;
    public:
        LinearFunction(double a, double b);
        double Evaluate(double x) override;
        void Solve() override;
        void PrintEquation() override;
};

class QuadraticFunction : public Function{
    private:
        const size_t index_;
        double a_,b_,c_;
    public:
        QuadraticFunction(double a, double b, double c);
        double Evaluate(double x) override;
        void Solve() override;
        void PrintEquation() override;
};

