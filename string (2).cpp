#include "vector.h"

template <class T> 
class String{
private:
    vector<T> array;
    std::size_t size_{};
public:
    
    String(String<T>&& other) {
        size_ = std::move(other.size_);
        array = std::move(other.array);
    }

    String(const String<T>& other) : size_{other.size_} {
        array = other.array;
    }
    
    String<T>& operator+= (const String<T>& other) {
        for(int i = 0; i < other.size_; ++i) {
            array.push_back(other[i]);
            size_++;
        }
        return *this;
    }

    String<T> operator+ (const String<T>& other) {
        String<T> help = *this;
        return help += other;
    }

    T& operator[] (int i) {
        return array[i];
    }

    const T& operator[] (int i) const {
        return array[i];
    }

    String& operator= (String<T>&& other){
        if (this == &other) {
            return *this;
        }
        size_  = std::move(other.size);
        array = std::move(other.array);
        return *this;
    }

    String& operator= (const String<T>& other){
        if (this == &other) {
            return *this;
        }
        size_ = std::move(other.size_);
        array = std::move(other.array);
        return *this;
    }

    std::size_t size() const{
        return size_;
    }
};