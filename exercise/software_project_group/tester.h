#include "agent.h"
#include <string>
#include <iostream>

class Tester: public Agent {
    char marker ;
    int flag ;
    int passed_num = 0 ;
public:
    Tester(int agent_id_, std::string& codes_, char marker_, int flag_): Agent(agent_id_, codes_), marker(marker_), flag(flag_) {}
    ~Tester() {}
    void action()
    {
        int sum = 0 ;
        for(char x: codes)
        {
            if(x == marker) sum ++ ;
        }
        if((sum % 2) == (flag % 2)) passed_num ++ ;
    }
    void report()
    {
        std::cout << "Tester " << get_agent_id() << ": " << passed_num << " tests passed" << std::endl ;
    }
} ;