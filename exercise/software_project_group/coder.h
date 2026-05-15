#include "agent.h"
#include <string>
#include <iostream>

class Coder: public Agent {
    int char_coded = 0;
public:
    Coder(int agent_id_, std::string& codes_): Agent(agent_id_, codes_) {}
    ~Coder() {}
    void action()
    {
        std::string code_addition ;
        std::cin >> code_addition ;
        codes += code_addition ;
        char_coded += code_addition.length() ;
    }
    void report()
    {
        std::cout << "Coder " << get_agent_id() << ": " << char_coded << " characters coded" << std::endl ;
    }
} ;