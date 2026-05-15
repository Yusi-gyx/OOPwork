#include<iostream>
#include<cstring>

class PalString {
    char* str ;
public:
    PalString(const char* str_c)
    {
        str = new char[2*strlen(str_c) + 1] ;
        strcpy(str, str_c) ;
        char* reverse_str = new char[strlen(str_c) + 1] ;
        for(int i = 0 ; i < strlen(str_c); i ++)
        {
            reverse_str [i] = str_c [strlen(str_c) - i - 1]; 
        }
        reverse_str [strlen(str_c)] = '\0';
        strcat(str, reverse_str) ;
        delete[] reverse_str ;
    } 
    ~PalString(){delete[] str ;} 
    PalString(const PalString& T){
        str = new char[strlen(T.str) + 1] ;
        strcpy(str, T.str);
    }
    char* getString() {return str ;}
    void changeString(const char* str_c) ;

    friend std::ostream& operator<<(std::ostream& out , const PalString& T) ;
} ;

void PalString::changeString(const char* str_c)
{
    delete[] str;
    str = new char[2*strlen(str_c) + 1];
    strcpy(str, str_c);
    char *reverse_str = new char[strlen(str_c) + 1];
    for (int i = 0; i < strlen(str_c); i++)
    {
        reverse_str[i] = str_c[strlen(str_c) - i - 1];
    }
    reverse_str[strlen(str_c)] = '\0';
    strcat(str, reverse_str);
    delete[] reverse_str;
}

std::ostream& operator<<(std::ostream& out , const PalString& T)
{
    out << T.str ;
    return out ;
}