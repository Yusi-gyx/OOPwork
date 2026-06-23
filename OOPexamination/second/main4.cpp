#include <iostream>
#include "agent.h"
using namespace std;

int main() {
    AgentTrace<string, 100> trace;
    trace.add("user", "first question", 2);
    trace.add("assistant", "first answer", 3);
    trace.add("user", "second question", 4);
    trace.add("tool:search", "web page", 5);

    trace[1] = "changed answer";
    trace["user"][1] = "modified question";

    cout << trace[0] << endl;
    cout << trace[1] << endl;
    cout << trace["user"][0] << endl;
    cout << trace["user"][1] << endl;
    cout << trace["tool:search"][0] << endl;
    return 0;
}
