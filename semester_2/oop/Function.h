#pragma once
#include <iostream>
#include <unordered_set>

class Function{
    public:
        virtual double Evaluate(double x) = 0;
        virtual void Solve() = 0;
        virtual void PrintEquation() = 0;
        virtual ~Function() = default;
        virtual size_t GetNumber() = 0;
        virtual bool IsLinear() = 0;
        virtual bool IsQuadratic() = 0;
    protected:
        std::unordered_set<double> solutions_;
        static size_t counter_;
};

class LinearFunction : public Function{
    private:
        double a_,b_;
        const size_t index_;
        void Calculate();
    public:
        bool IsLinear() override;
        bool IsQuadratic() override;
        LinearFunction(double a, double b);
        double Evaluate(double x) override;
        void Solve() override;
        void PrintEquation() override;
        size_t GetNumber() override;
};

class QuadraticFunction : public Function{
    private:
        double a_,b_,c_;
        const size_t index_;
        void Calculate();
    public:
        bool IsLinear() override;
        bool IsQuadratic() override;
        QuadraticFunction(double a, double b, double c);
        double Evaluate(double x) override;
        void Solve() override;
        void PrintEquation() override;
        size_t GetNumber() override;
};

