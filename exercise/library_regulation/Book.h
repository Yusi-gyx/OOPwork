#pragma once
#include <string>
#include <iostream>

template<typename T> 
class Book {
    std::string BookName;
    std::string Author;
    T Pages;
public:
    Book(std::string BookName_, std::string Author_, T Pages_): BookName(BookName_), Author(Author_), Pages(Pages_){}
    ~Book() {}

    std::string getName()
    {
        return BookName;
    }

    void show()
    {
        std::cout << "Book name: " << BookName << ", Author: " << Author << ", Pages: " << Pages << std::endl ;
    }

    bool operator<(const Book<T>& other)
    {
        return Pages < other.Pages ;
    }
};