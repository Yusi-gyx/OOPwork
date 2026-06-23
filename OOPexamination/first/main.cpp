#include <iostream>
#include <map>
#include <string>

#include "FogLamp.h"

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::map<std::string, Lamp*> lamps;
    std::map<std::string, Inspection*> records;

    for (int i = 0; i < n; ++i) {
        std::string op;
        std::cin >> op;

        if (op == "steady") {
            std::string id, color;
            int level;
            std::cin >> id >> color >> level;
            delete lamps[id];
            lamps[id] = new SteadyLamp(color, level);
        } else if (op == "pulse") {
            std::string id, color;
            int low, high;
            std::cin >> id >> color >> low >> high;
            delete lamps[id];
            lamps[id] = new PulseLamp(color, low, high);
        } else if (op == "up") {
            std::string id;
            int d;
            std::cin >> id >> d;
            lamps[id]->up(d);
        } else if (op == "live") {
            std::string rid, id;
            std::cin >> rid >> id;
            delete records[rid];
            records[rid] = new Inspection(lamps[id], false);
        } else if (op == "freeze") {
            std::string rid, id;
            std::cin >> rid >> id;
            delete records[rid];
            records[rid] = new Inspection(lamps[id], true);
        } else if (op == "copy") {
            std::string rid2, rid1;
            std::cin >> rid2 >> rid1;
            delete records[rid2];
            records[rid2] = new Inspection(*records[rid1]);
        } else if (op == "assign") {
            std::string rid2, rid1;
            std::cin >> rid2 >> rid1;
            *records[rid2] = *records[rid1];
        } else if (op == "dropRecord") {
            std::string rid;
            std::cin >> rid;
            delete records[rid];
            records.erase(rid);
        } else if (op == "show") {
            std::string rid;
            std::cin >> rid;
            std::cout << rid << " -> "
                      << records[rid]->report() << "/"
                      << records[rid]->power() << '\n';
        }
    }

    for (auto& item : records) {
        delete item.second;
    }
    for (auto& item : lamps) {
        delete item.second;
    }

    return 0;
}
