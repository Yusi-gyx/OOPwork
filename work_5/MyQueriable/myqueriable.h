#include <vector>
#include <functional>

template<typename T>
class MyQueriable {   
public:
    std::vector<T> arr;
    MyQueriable where(std::function<bool(T)> f);
    MyQueriable apply(std::function<T(T)> f);
    T sum();
    class iterator{
        T* ptr;
    public:
        iterator(T* p): ptr(p) {}
        T& operator*() {return *ptr;}
        iterator& operator++() 
        {
            ptr ++;
            return *this;
        }
        bool operator!=(const iterator& other)
        {
            return ptr != other.ptr;
        }
    };

    iterator begin() 
    {
        if(arr.empty()) return iterator(nullptr);
        else return &arr[0];
    }
    iterator end() 
    {
        if(arr.empty()) return iterator(nullptr);
        else return &arr[0] + arr.size();
    }

    template<typename U, size_t N>
    friend MyQueriable<T> from(const T (&container)[N]);
    template<typename U>
    friend MyQueriable<T> from(const std::vector<T>& container);
};

template<typename T, size_t N>
MyQueriable<T> from(const T (&container)[N])
{
    MyQueriable<T> temp;
    for(auto x: container)
    {
        temp.arr.push_back(x);
    }
    return temp ;
}

template<typename T>
MyQueriable<T> from(const std::vector<T>& container)
{
    MyQueriable<T> temp;
    for(auto x: container)
    {
        temp.arr.push_back(x);
    }
    return temp ;
}

template<typename T>
MyQueriable<T> MyQueriable<T>::where(std::function<bool(T)> f)
{
    MyQueriable<T> temp;
    for(auto x: arr)
    {
        if(f(x)) temp.arr.push_back(x);
    }
    return temp;
}

template<typename T>
MyQueriable<T> MyQueriable<T>::apply(std::function<T(T)> f)
{
    MyQueriable<T> temp;
    for(auto x: arr)
    {
        temp.arr.push_back(f(x));
    }
    return temp;
}

template<typename T>
T MyQueriable<T>::sum()
{
    T result = 0 ;
    for(auto x: arr)
    {
        result += x;
    }
    return result;
}