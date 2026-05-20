#pragma once
#include <vector>
#include <functional>

template<typename T>
class MyQueriable {   
    std::vector<T> arr;
public:
    MyQueriable where(std::function<bool(T)> f);
    MyQueriable apply(std::function<T(T)> f);
    T sum() const;
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
        bool operator!=(const iterator& other){return ptr != other.ptr;}
        //这里不需要重载其他符号和函数（这个题没有用到）
    };

    iterator begin() 
    {
        return arr.data();
    }
    iterator end() 
    {
        return arr.data() + arr.size();
    }

    std::vector<T>& transform() {return arr;} 
    //返回引用时不要用取地址符，这将返回一个指针

    //这里的友元函数需要是模板函数，但是注意参数类型的名称要和模板类的不一样
    template<typename U, size_t N>
    friend MyQueriable<U> from(const T (&container)[N]);
    template<typename U>
    friend MyQueriable<U> from(const std::vector<T>& container);
};

template<typename T, size_t N>
MyQueriable<T> from(const T (&container)[N])
{
    MyQueriable<T> temp;
    for(auto x: container)
    {
        temp.transform().push_back(x);
    }
    return temp ;
}

template<typename T>
MyQueriable<T> from(const std::vector<T>& container)
{
    MyQueriable<T> temp;
    for(auto x: container)
    {
        temp.transform().push_back(x);
    }
    return temp ;
}

template<typename T>
MyQueriable<T> MyQueriable<T>::where(std::function<bool(T)> f)
{
    MyQueriable<T> temp;
    for(auto x: arr)
    {
        if(f(x)) temp.transform().push_back(x);
    }
    return temp;
}

template<typename T>
MyQueriable<T> MyQueriable<T>::apply(std::function<T(T)> f)
{
    MyQueriable<T> temp;
    for(auto x: arr)
    {
        temp.transform().push_back(f(x));
    }
    return temp;
}

template<typename T>
T MyQueriable<T>::sum() const
{
    T result = 0 ;
    for(auto x: arr)
    {
        result += x;
    }
    return result;
}