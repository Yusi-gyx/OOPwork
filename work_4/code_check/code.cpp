#include <iostream>
using namespace std;

class Agent {
public:
    void work() {
        cout << "Agent is working on general tasks." << endl;
    }
};

class CEOAgent : public Agent {
public:
    int* strategic_plans;
    int plan_count;

    CEOAgent(int plans = 5) : plan_count(plans) {
        strategic_plans = new int[plan_count];
    }

    ~CEOAgent() {
        delete[] strategic_plans;
    }

    void work() {
        cout << "CEOAgent is making strategic decisions." << endl;
    }
};

class CTOAgent : public Agent {
public:
    int* tech_plans;
    int plan_count;

    CTOAgent(int plans = 5) : plan_count(plans) {
        tech_plans = new int[plan_count];
    }

    ~CTOAgent() {
        delete[] tech_plans;
    }

    void work() {
        cout << "CTOAgent is designing architecture." << endl;
    }
};

class AgentCompany {
public:
    CEOAgent ceo;
    CTOAgent cto;

    void resetCTO(int plans = 5) {
          CTOAgent new_cto(plans);
        this->cto = new_cto; 
    }

    Agent getCEO() {
        return this->ceo;
    }
};
