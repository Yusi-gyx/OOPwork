#include <iostream>
#include "agent.h"
using namespace std;

int main() {
    AgentTrace<string, 10> trace(
        {"system", "user", "assistant", "tool:search"},
        {"rules", "hello", "answer", "page"},
        {2, 3, 4, 5}
    );

    vector<string> memories = trace.retrieve(3, [](const string& s) {
        return (int)s.size();
    });
    for (const auto& item : memories) {
        cout << item << endl;
    }

    auto stats = trace.tool_stats();
    for (const auto& item : stats) {
        cout << item.first << " " << item.second << endl;
    }

    trace.compact();
    cout << trace.token_sum() << endl;
    cout << trace << endl;
    return 0;
}
