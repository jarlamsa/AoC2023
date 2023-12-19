#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <chrono>
#include <map>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct part {
    int x;
    int m;
    int a;
    int s;
};

struct rule {
    uint32_t value = 0;
    // 0 straight to goal
    // 1 - 4 lower than
    // 5 - 8 larger than
    // x, m, a, s
    uint32_t comparison = 0;
    string goal;
};

// Directions: 1 up, 2 left, 3 down, 4 right
int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;

    uint32_t sum = 0;
    map<string, vector<struct rule>> rules;
    queue<struct part> parts;
    vector<struct part> accepted;

    // Are we reading rules or parts
    bool reading_parts = false;

	while(getline(infile, buffer)) {
        if (buffer.empty()) {
            reading_parts = true;
            continue;
        }
        buffer.erase(remove(buffer.begin(), buffer.end(), '}'), buffer.end());
        // We are reading rules
        if (!reading_parts) {
            size_t pos = buffer.find_first_of('{');
            string rule_name = buffer.substr(0, pos);
            string arule;
            vector<struct rule> workflow_rules;

            stringstream ss(buffer.substr(pos+1));
            while (getline(ss, arule, ',')) {
                struct rule r;
                size_t cpos = arule.find_first_of(':');
                if (cpos != string::npos) {
                    r.goal = arule.substr(cpos+1);
                    int comparison = 0;
                    if (arule[0] == 'x') comparison = 1;
                    else if (arule[0] == 'm') comparison = 2;
                    else if (arule[0] == 'a') comparison = 3;
                    else if (arule[0] == 's') comparison = 4;
                    if (arule.find_first_of('>') != string::npos) {
                        comparison += 4;
                    }
                    r.comparison = comparison;
                    r.value = stoi(arule.substr(2, cpos - 1));
                } else {
                    r.goal = arule;
                }
                workflow_rules.push_back(r);
            }
            rules[rule_name] = workflow_rules;
        } else {
            stringstream ss(buffer.substr(1));
            struct part p;
            string apart;
            int i = 0;
            while (getline(ss, apart, ',')) {
                int amount = stoi(apart.substr(2));
                if (i==0) {
                    p.x = amount;
                } else if (i==1) {
                    p.m = amount;
                } else if (i==2) {
                    p.a = amount;
                } else if (i==3) {
                    p.s = amount;
                }
                i++;
            }
            parts.push(p);
        }
	}

    while(!parts.empty()) {
        string current = "in";
        struct part p = parts.front();
        parts.pop();
        // Doing this while the part is accepted or rejected
        while(true) {
            vector<struct rule> rulelist = rules[current];
            bool rule_applies = false;
            for (auto r : rulelist) {
                switch (r.comparison) {
                    case 0:
                        rule_applies = true;
                        break;
                    case 1:
                        if (p.x < r.value)
                            rule_applies = true;
                        break;
                    case 2:
                        if (p.m < r.value)
                            rule_applies = true;
                        break;
                    case 3:
                        if (p.a < r.value)
                            rule_applies = true;
                        break;
                    case 4:
                        if (p.s < r.value)
                            rule_applies = true;
                        break;
                    case 5:
                        if (p.x > r.value)
                            rule_applies = true;
                        break;
                    case 6:
                        if (p.m > r.value)
                            rule_applies = true;
                        break;
                    case 7:
                        if (p.a > r.value)
                            rule_applies = true;
                        break;
                    case 8:
                        if (p.s > r.value)
                            rule_applies = true;
                        break;
                }
                if (rule_applies) {
                    current = r.goal;
                    break;
                }
            }
            if (current == "A") {
                accepted.push_back(p);
                break;
            } else if (current == "R") {
                break;
            }
        }
    }

    for (auto r : accepted) {
        sum += r.x;
        sum += r.m;
        sum += r.a;
        sum += r.s;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Rating of accepted parts " << sum << " time taken " << duration.count() << " us" << endl;

}
