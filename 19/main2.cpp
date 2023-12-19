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

struct part_range {
    string workflow;
    uint64_t min_values[4];
    uint64_t max_values[4];
};

struct rule {
    uint64_t amount = 0;
    // 0 straight to goal
    // 1 - 4 lower than
    // 5 - 8 larger than
    // x, m, a, s
    uint64_t comparison = 0;
    string goal;
};

// Directions: 1 up, 2 left, 3 down, 4 right
int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;

    uint64_t sum = 0;
    map<string, vector<struct rule>> rules;
    vector<struct part_range> accepted;
    queue<struct part_range> ranges;

    struct part_range original;
    original.workflow = "in";
    for (int i = 0; i < 4; i++) {
        original.min_values[i] = 1;
        original.max_values[i] = 4000;
    }

    ranges.push(original);

    // Are we reading rules or parts
    bool reading_parts = false;

	while(getline(infile, buffer)) {
        if (buffer.empty()) {
            reading_parts = true;
            break;;
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
                    r.amount = stoi(arule.substr(2, cpos - 1));
                } else {
                    r.goal = arule;
                }
                workflow_rules.push_back(r);
            }
            rules[rule_name] = workflow_rules;
        }
	}

    while(!ranges.empty()) {
        struct part_range p = ranges.front();
        ranges.pop();
        string current = p.workflow;
        // Doing this while the part is accepted or rejected
        while(true) {
            vector<struct rule> rulelist = rules[current];
            bool rule_applies = false;
            for (auto r : rulelist) {
                if (r.comparison == 0) {
                    current = r.goal;
                    break;
                }

                bool partial_range = false;

                struct part_range partial;
                for (int i = 0; i < 4; i++) {
                    partial.min_values[i] = p.min_values[i];
                    partial.max_values[i] = p.max_values[i];
                }
                partial.workflow = current;
                // Lower than limit
                uint64_t i = r.comparison;
                if (i < 5) {
                    if (p.min_values[i-1] >= r.amount) {
                        continue;
                    } else if (p.max_values[i-1] < r.amount) {
                        current = r.goal;
                        break;
                    } else {
                        p.max_values[i-1] = r.amount - 1;
                        partial.min_values[i-1] = r.amount;
                        partial_range = true;
                    }
                } else {
                    if (p.max_values[i-5] <= r.amount) {
                        continue;
                    } else if (p.min_values[i-5] > r.amount) {
                        current = r.goal;
                        break;
                    } else {
                        p.min_values[i-5] = r.amount + 1;
                        partial.max_values[i-5] = r.amount;
                        partial_range = true;
                    }
                }

                if (partial_range) {
                    current = r.goal;
                    ranges.push(partial);
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
        uint64_t range_sum = 1;
        for (int i = 0; i < 4; i++) {
            range_sum *= (r.max_values[i] - r.min_values[i] + 1);
        }
        sum += range_sum;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Rating of accepted parts " << sum << " time taken " << duration.count() << " us" << endl;

}
