#include <iostream>
#include "agent.h"
using namespace std;

int main() {
    AgentTrace<string, 20> trace;
    cout << trace.token_sum() << endl;
    cout << trace.add("system", "rules", 3) << endl;
    cout << trace.add("user", "hello", 2) << endl;
    cout << trace.get(0) << " " << trace.get(1) << endl;
    trace.set(1, "changed");
    cout << trace.get(1) << endl;

    AgentTrace<int, 10> nums({"user", "assistant", "user"}, {7, 8, 9}, {1, 2, 3});
    cout << nums.token_sum() << endl;
    vector<int> user_ids = nums.ids("user");
    for (int i = 0; i < (int)user_ids.size(); ++i) {
        if (i) cout << " ";
        cout << user_ids[i];
    }
    cout << endl;

    AgentTrace<string, 5> defaults({"system", "user"});
    cout << "[" << defaults.get(0) << "][" << defaults.get(1) << "] " << defaults.token_sum() << endl;
    return 0;
}
