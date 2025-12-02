#pragma once
#include <initializer_list>

class Vector {
private:
    int* data_; //указатель на дин. массив
    int size_; //кол-во элементов
    int capacity_; //выделенный размер

    void resize(); //изменение capacity

public:
    //*конструкторы
    Vector(); //по умолчанию
    Vector(int size); //принимает размер, заполняет нулями
    Vector(std::initializer_list<int> list); //{1,2,3,4,5}
    Vector(const Vector& other); //копирования
    ~Vector(); //деструктор
    Vector& operator=(Vector& other); //оператор присваивания ?
    //Vector& operator(); ?
    void Swap();
    //операторы индексирования const и неconst
    void Size();  //getSize
    void Capacity();  //getCapacity
    void PushBack(); //добавляет элемент в конец вектора + реаллокация при необх
    void PopBack(); //удаляет последний элемент, capacity не меняет
    void Clear(); //делает контейнер пустым, capacity не меняет
    void Reserve(); //задать новую capacity (больше)

};
