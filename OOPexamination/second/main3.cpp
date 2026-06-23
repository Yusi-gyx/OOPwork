#include <iostream>
#include "agent.h"
using namespace std;

int main() {
    AgentTrace<string, 100> trace({"user", "assistant", "tool:search"}, {"hello", "hi", "page"}, {2, 2, 3});

    for (auto& content : trace) {
        cout << content << endl;
    }

    auto it = trace.begin();
    cout << *it << endl;
    *it = "modified";
    cout << trace.get(0) << endl;

    auto old = it++;
    cout << *old << " " << *it << endl;
    ++it;
    cout << (*it == "page") << endl;
    cout << (it != trace.end()) << endl;
    ++it;
    cout << (it == trace.end()) << endl;
    return 0;
}
