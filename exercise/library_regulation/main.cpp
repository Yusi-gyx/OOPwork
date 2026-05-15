#include<iostream>
#include"Book.h"
#include"Library.h"
using namespace std;

int main() {

    Library<int> library;
    Book<int> book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book<int> book2("To Kill a Mockingbird", "Harper Lee", 324);

    library.addBook(book1);
    library.addBook(book2);
    library.show();

    library.borrowBook("The Catcher in the Rye");
    
    library.borrowBook("1984");

    Book<int> book3("1984", "George Orwell", 328);
    if (book2 < book3) book2.show();
    else book3.show();
	
    return 0;
}
