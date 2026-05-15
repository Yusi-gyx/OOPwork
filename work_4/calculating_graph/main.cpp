#include <iostream>
#include <string>
#include "Value.h"
#include "Constant.h"
#include "Plus.h"
#include "Sub.h"
#include "Multiply.h"
int n;
Value *v[100001];
std::string s;

class Print: public Value{
    int obj ;
public:
    Print(int a): obj(a) {}
    ~Print() {}
    int calc() {return v [obj]->calc() ;}
    int getObj() {return obj ;}
} ;

int main()
{
    std::cin >> n;
    int a, b;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> s;
        if(s == "Constant")
        {
            std::cin >> a ;
            v [i] = new Constant(a) ;
        }
        else if(s == "Plus")
        {
            std::cin >> a >> b ;
            v [i] = new Plus(v [a], v [b]) ;
        }
        else if(s == "Sub")
        {
            std::cin >> a >> b ;
            v [i] = new Sub(v [a], v [b]) ;
        }
        else if(s == "Multiply")
        {
            std::cin >> a >> b ;
            v [i] = new Multiply(v [a], v [b]) ;
        }
        else if(s == "Print")
        {
            std::cin >> a;
            while (dynamic_cast<Print *>(v[a]))
            {
                a = dynamic_cast<Print*>(v[a])->getObj() ;
            }
            v[i] = new Print(a);
            std::cout << v[a]->calc() << std::endl ;
        }
        else if(s == "Modify")
        {
        	std::cin >> a >> b ;
            while (dynamic_cast<Print *>(v[a]))
            {
                a = dynamic_cast<Print*>(v[a])->getObj() ;
            }
            v [i] = new Print(a) ;
            Constant* temp = dynamic_cast<Constant*>(v [a]) ;
            temp->setNum(b) ;
        }
    }
	return 0;
}