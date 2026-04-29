#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>



struct S {
    int x;
    S(int x): x(x) {}
};

template <typename T>
class vector {
private:
    T* arr_;
    size_t sz_;
    size_t cap_;
public:

    vector(): arr_(nullptr), sz_(0), cap_(0) {
    }

    void reserve(size_t newcap) {
        if (newcap <= cap_) {
            return;
        }
        
        //T* newarr = new T[newcap];

        T* newarr = reinterpret_cast<T*>(new char[newcap * sizeof(T)]);
        size_t newindex = 0;
        try {
            // new (newarr + sz_) T(value);
            for (; newindex < sz_; ++newindex) {
                //newarr[i] = arr_[i]; 
                // placement new
                // new (ptr) ctor;
                new (newarr + newindex) T(std::move_if_noexcept(arr_[newindex])); 
            }

        } catch(...) { 
            for (size_t oldindex = 0; oldindex < newindex; ++oldindex) {
                (newarr + oldindex)->~T(); 
            }
            delete[] reinterpret_cast<char*>(newarr); // ?
            throw;
        }

        for (size_t i = 0; i < sz_; ++i) {
            (arr_ + i)->~T(); 
        }
        delete[] reinterpret_cast<char*>(arr_); // ?
        arr_ = newarr;
        cap_ = newcap;
    }


    void push_back(const T& value) {
        if (sz_ == cap_) {
            reserve(cap_ == 0u ? 1u : cap_ * 2u);
        }

        new (arr_ + sz_) T(value);
        ++sz_;
    }

    void push_back(T&& value) {
        if (sz_ == cap_) {
            reserve(cap_ == 0u ? 1u : cap_ * 2u);
        }

        new (arr_ + sz_) T(std::move(value));
        ++sz_;
    }

    ~vector() {
        for (size_t i = 0; i < sz_; ++i) {
            (arr_ + i)->~T(); 
        }
        delete[] reinterpret_cast<char*>(arr_); // ?
    }
};


template<>
class vector<bool> {
    char* arr_;
    size_t cap_;
    size_t sz_;

    struct BitReference {
        char* cell;
        size_t num;
        
        BitReference(char* cell, size_t num)
            : cell(cell), num(num) {}
        
        void operator[](bool value) {
            if (value) {
                *cell |= (1 << num);
            } else {
                *cell &= ~(1 << num); 
            }
        }
        

    };
public:

    BitReference operator[](size_t index) {
        return BitReference(arr_ + index / 8, index % 8);
    }
};


template <typename T>
void f(T) = delete;


int main() {

    //vector<int> v;
    //v.push_back(1);

    std::vector<bool> vb(10, true);
    vb[5] = false;
    
    f(vb[5]);

    return 0;
}
