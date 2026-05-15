#include "agent.h"
#include "coder.h"
#include "tester.h"
#include <string>
#include <iostream>
Agent* Agent::create_agent(int agent_type, int id, std::string& codes)
{
    if(agent_type == 0)
    {
        return new Coder(id, codes);
    }
    else
    {
        char marker ;
        int flag ;
        std::cin >> marker >> flag ;
        return new Tester(id, codes, marker, flag) ;
    }
}