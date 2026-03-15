#pragma once
#include <iostream>
#include <unordered_set>

class Function{
    public:
        virtual double Evaluate(double x) const = 0;
        virtual void Solve(std::ostream& os) = 0;
        virtual void PrintEquation(std::ostream& os) const = 0;
        virtual ~Function() = default;
        virtual void Calculate() = 0;
        virtual size_t GetNumber() const = 0;
        virtual bool IsLinear() const = 0;
        virtual bool IsQuadratic() const = 0;
        virtual double GetA() const = 0;
        virtual double GetB() const = 0;
    protected:
        std::unordered_set<double> solutions_;
        static size_t counter_;
};

class LinearFunction : public Function{
    private:
        double a_,b_;
        const size_t index_;
    public:
        void Calculate() override;
        bool IsLinear() const override;
        bool IsQuadratic() const override;
        LinearFunction(double a, double b);
        double Evaluate(double x) const override;
        void Solve(std::ostream& os) override;
        void PrintEquation(std::ostream& os) const override;
        size_t GetNumber() const override;
        double GetA() const override;
        double GetB() const override;
};

class QuadraticFunction : public Function{
    private:
        double a_,b_,c_;
        const size_t index_;
    public:
        void Calculate() override;
        bool IsLinear() const override;
        bool IsQuadratic() const override;
        QuadraticFunction(double a, double b, double c);
        double Evaluate(double x) const override;
        void Solve(std::ostream& os) override;
        void PrintEquation(std::ostream& os) const override;
        size_t GetNumber() const override;
        double GetA() const override;
        double GetB() const override;
        double GetC() const;
};
