#include <iostream>
#include "agent.h"
using namespace std;

int main() {
    AgentTrace<string, 100> trace(
        {"system", "user", "assistant"},
        {"rules", "ask", "answer"},
        {3, 5, 7}
    );

    AgentTrace<string, 100> copy = trace;
    cout << (trace == copy) << " " << (trace != copy) << endl;

    copy.set(2, "changed");
    cout << (trace == copy) << " " << (trace != copy) << endl;

    AgentTrace<string, 100> assigned;
    assigned = copy;
    assigned.set(0, "new-rules");
    cout << copy.get(0) << " " << assigned.get(0) << endl;

    cout << trace << endl;
    return 0;
}
