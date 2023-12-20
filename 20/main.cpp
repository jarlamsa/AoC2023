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

    for (int i = 0; i < 1000; i++) {
        struct signal sign;
        sign.state = 0;
        sign.recv = "broadcaster";
        sign.snd = "button";
        signals.push(sign);
        while(!signals.empty()) {
            struct signal s;
            s = signals.front();
            signals.pop();
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
                for (auto o : modules[s.recv].memory) {
                    if (o.second == false) {
                        all_high = false;
                    }
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
    }

    uint64_t totals = low_signals * high_signals;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Multiplied total of signals " << totals << " time taken " << duration.count() << " us" << endl;

}
