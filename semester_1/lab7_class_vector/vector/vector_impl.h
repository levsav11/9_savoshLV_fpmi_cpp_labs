#pragma once
#include <iostream>
#include <initializer_list>

class Vector {
private:
    int* data_; //указатель на дин. массив
    size_t size_; //кол-во элементов
    size_t capacity_; //выделенный размер
public:
    //*конструкторы
    Vector(); //по умолчанию
    Vector(size_t size); //принимает размер, заполняет нулями
    Vector(std::initializer_list<int> list); //{1,2,3,4,5}
    Vector(const Vector& other); //копирования
    Vector& operator=(const Vector& other); //оператор присваивания копированием
    ~Vector(); //деструктор
    void Swap(Vector& other);  //перестановка
    const int& operator[](size_t index) const; //операторы индексирования const и неconst
    const int& At (size_t index) const; //[] с проверкой
    int& At(size_t index);
    int& operator[](size_t index); //должен позволять менять
    size_t Size() const;  //getSize
    size_t Capacity() const;  //getCapacity
    void PushBack(int elem); //добавляет элемент в конец вектора + реаллокация при необх
    void PopBack(); //удаляет последний элемент, capacity не меняет
    void Clear(); //делает контейнер пустым, capacity не меняет
    void Reserve(size_t newCapacity); //задать новую capacity (больше)
    friend std::ostream& operator<<(std::ostream& os, const Vector& v); //оператор вывода, не член класса
};

