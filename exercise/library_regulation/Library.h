#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Book.h"

template <typename T> 
class Library {
    std::vector<Book<T>> Library_books;
public:
    void addBook(const Book<T>& book)
    {
        Library_books.push_back(book);
    }

    void show()
    {
        for(auto x: Library_books)
        {
            x.show();
        }
    }

    void borrowBook(const std::string& title)
    {
        for(auto x: Library_books)
        {
            if(x.getName() == title) 
            {
                std::cout << "Books Checked out " << title << "." << std::endl;
                return;
            }
        }
        std::cout << "Book " << title << " does not exist." << std::endl ;
    }
};