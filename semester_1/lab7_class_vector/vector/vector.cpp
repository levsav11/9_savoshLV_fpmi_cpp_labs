#include <vector.h>

void Vector::Reserve(int newCapacity){
    if (newCapacity <= capacity_) return;
    int* oldData = data_;
    int oldSize = size_;
    data_ = new int[newCapacity];
    for (int i = 0; i < oldSize; ++i){
        data_[i] = oldData[i];
    }
    delete[] oldData;
    capacity_ = newCapacity;
}
Vector::Vector()
:data_(nullptr),
 size_(0),
 capacity_(0){};
Vector::Vector(int size)
:data_(new int[size]),
 size_(size),
 capacity_(size){
    for (int i = 0; i < size; ++i){
        data_[i] = 0;
    }
}
Vector::Vector(std::initializer_list<int> list)
:data_(nullptr),
 size_(static_cast<int>(list.size())), capacity_(static_cast<int>(list.size())){
    data_ = new int[capacity_];
    int index = 0;
    for (int value : list){
        data_[index] = value;
        ++index;
    }
}
Vector::Vector(const Vector& other)
:data_(nullptr),
 size_(other.size_),
 capacity_(other.capacity_){
    if (capacity_ > 0){
        data_ = new int[size_];
        for (int i = 0; i < size_; ++i){
            data_[i] = other.data_[i];
        }
    }
}
Vector& Vector::operator=(const Vector& other){
    if (this == &other){
        return *this;
    }
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new int[capacity_];
    for (int i = 0; i < other.size_; ++i){
        data_[i] = other.data_[i];
    }
    return *this;
}
int& Vector::operator[](int index){
    return data_[index];
 }
const int& Vector::operator[](int index) const {
    return data_[index];
 }
Vector::~Vector(){
    delete[] data_;
    /*data_ = nullptr;
    size_ = 0;
    capacity_ = 0;*/
}
void Vector::Swap(Vector& other){
    int* tmpData = data_;
    data_ = other.data_;
    other.data_ = tmpData;

    int tmpSize = size_;
    size_ = other.size_;
    other.size_ = tmpSize;

    int tmpCapacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tmpCapacity;
}
int Vector::Size() const{
    return size_;
}
int Vector::Capacity() const{
    return capacity_;
}
void Vector::PushBack(int elem){
    if (capacity_ == size_){
        int newCapacity = (capacity_ == 0 ? 1 : 2 * capacity_);
        Reserve(newCapacity);
    }
    data_[size_] = elem;
    ++size_;
}
void Vector::PopBack(){
    if (size_ > 0){
    --size_;
    }
}
void Vector::Clear(){
    size_ = 0;
}
std::ostream& operator<<(std::ostream& os,const Vector& v){
    os << '[';
    for (int i = 0; i < v.size_; ++i){
        os << v.data_[i];
        if (i < v.size_ - 1){
            os << ", ";
        }
    }
    os << ']';
    return os;
}