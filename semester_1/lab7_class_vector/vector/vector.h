#pragma once
#include <iostream>
#include <initializer_list>

class Vector {
private:
    int* data_; //указатель на дин. массив
    int size_; //кол-во элементов
    int capacity_; //выделенный размер
public:
    //*конструкторы
    Vector(); //по умолчанию
    Vector(int size); //принимает размер, заполняет нулями
    Vector(std::initializer_list<int> list); //{1,2,3,4,5}
    Vector(const Vector& other); //копирования
    Vector& operator=(const Vector& other); //оператор присваивания копированием
    ~Vector(); //деструктор
    void Swap(Vector& other);
    //операторы индексирования const и неconst
    const int& operator[](int index) const;
    int& operator[](int index); //должен позволять менять
    int Size();  //getSize
    int Capacity();  //getCapacity
    void PushBack(int elem); //добавляет элемент в конец вектора + реаллокация при необх
    void PopBack(); //удаляет последний элемент, capacity не меняет
    void Clear(); //делает контейнер пустым, capacity не меняет
    void Reserve(int newCapacity); //задать новую capacity (больше)
    friend std::ostream& operator<<(std::ostream& os, const Vector& v); //оператор вывода, не член класса
};

