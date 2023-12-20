#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <chrono>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace std::chrono;

struct module {
    // 0 broadcaster
    // 1 flip-flop
    // 2 conjunction
    uint32_t type;
    string name;
    bool state = false;
    vector<string> output;
    map<string, bool> memory;
};

struct signal {
    bool state;
    string recv;
    string snd;
};

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;

    uint32_t sum = 0;
    map<string, struct module> modules;
    queue<struct signal> signals;

    int true_memories[4] = {0};

	while(getline(infile, buffer)) {
        struct module m;
        size_t pos = buffer.find_first_of(' ');
        if (buffer[0] == '%') {
            m.type = 1;
            m.name = buffer.substr(1, pos - 1);
        } else if (buffer[0] == '&') {
            m.type = 2;
            m.name = buffer.substr(1, pos - 1);
        } else {
            m.type = 0;
            m.name = buffer.substr(0, pos);
        }
        pos = buffer.find_first_of('>');

        stringstream ss(buffer.substr(pos+2));
        string output;

        while (getline(ss, output, ',')) {
            output.erase(0, output.find_first_not_of(' '));
            m.output.push_back(output);
        }
        modules[m.name] = m;
	}

    // Initialize modules
    // Connect outputs to memory of conjunctions
    for (auto &t : modules) {
        struct module &m = t.second;
        for (auto & s : m.output) {
            if (modules[s].type == 2) {
                modules[s].memory[m.name] = false;
            }
        }
    }

    uint32_t low_signals = 0;
    uint32_t high_signals = 0;

    for (uint64_t i = 0; i < 10000000000; i++) {
        bool processing = true;
        struct signal sign;
        sign.state = 0;
        sign.recv = "broadcaster";
        sign.snd = "button";
        signals.push(sign);
        while(!signals.empty()) {
            struct signal s;
            s = signals.front();
            signals.pop();
            if (s.recv == "rx" && s.state == false) {
                processing = false;
                break;
            }
            if (s.state) {
                high_signals++;
            } else {
                low_signals++;
            }

            if (modules[s.recv].type == 1) {
                if (s.state == 1) {
                    continue;
                } else {
                    modules[s.recv].state = !modules[s.recv].state;
                    s.state = modules[s.recv].state;
                }
            } else if (modules[s.recv].type == 2) {
                modules[s.recv].memory[s.snd] = s.state;
                bool all_high = true;
                uint32_t count = 0;
                int j = 0;
                for (auto o : modules[s.recv].memory) {
                    if (s.recv == "df") {
                        if (o.second == true) {
                            true_memories[j] = i+1;
                        }
                    }
                    if (o.second == false) {
                        all_high = false;
                    }
                    j++;
                }

                if (all_high) {
                    s.state = false;
                } else {
                    s.state = true;
                }
            }

            for (auto o : modules[s.recv].output) {
                struct signal ns;
                ns.state = s.state;
                ns.recv = o;
                ns.snd = modules[s.recv].name;
                signals.push(ns);
            }
        }
        bool cycles_found = true;
        for (int j = 0; j < 4; j++) {
            if (true_memories[j] == 0 ) {
                cycles_found = false;
            }
        }
        if (cycles_found) {
            break;
        }
    }

    uint64_t rounds = 1;

    for (int i = 0; i < 4; i++) {
        rounds = lcm(true_memories[i], rounds);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Total rounds needed " << rounds << " time taken " << duration.count() << " us" << endl;

}
