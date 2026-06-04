#pragma once 

template<typename T>
class Line {
    T k;
    T b;
public:
    Line(T k_, T b_):k(k_), b(b_) {}
    Line(T k_):k(k_) {b = 0;}
    T getk() const {return k;}
    T getb() const {return b;}
    bool intersect(const Line& l) const;
    void show() const;
    bool operator<(const Line<T>& l) const;
};