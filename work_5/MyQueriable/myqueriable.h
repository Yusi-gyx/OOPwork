#pragma once
#include <vector>
#include <functional>

template <typename T>
class MyQueriable
{
    std::vector<T> arr;

public:
    MyQueriable() = default;
    MyQueriable(const std::vector<T>& obj): arr(obj) {}
    MyQueriable<T> where(std::function<bool(T)> f)
    {
        MyQueriable<T> temp;
        for (auto x : arr)
        {
            if (f(x))
                temp.arr.push_back(x);
        }
        return temp;
    }

    MyQueriable<T> apply(std::function<T(T)> f)
    {
        MyQueriable<T> temp;
        for (auto x : arr)
        {
            temp.arr.push_back(f(x));
        }
        return temp;
    }

    T sum() const
    {
        T result = 0;
        for (auto x : arr)
        {
            result += x;
        }
        return result;
    }

    auto begin() {return arr.begin();}
    auto end() {return arr.end();}
};

//类外进行实现
template<typename U, size_t N>
MyQueriable<U> from(const U (&container)[N])
{
    std::vector<U> temp;
    for (auto x : container)
    {
        temp.push_back(x);
    }
    return MyQueriable<U>(temp);
}

template<typename U>
MyQueriable<U> from(const std::vector<U>& container)
{
    std::vector<U> temp;
    for (auto x : container)
    {
        temp.push_back(x);
    }
    return MyQueriable<U>(temp);
}
