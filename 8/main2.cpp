#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool areNodesAtEnd(std::vector<int> intervals) {
    for (auto i : intervals) {
        if (i == 0) {
            return false;
        }
    }

    return true;
}

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    std::map<std::string, std::pair<string, string>> desert_map;
    string instructions;
    std::vector<string> starting_nodes;
    std::vector<int> intervals;

	while(getline(infile, buffer)) {
        if (instructions.empty()) {
            instructions = buffer;
            continue;
        } else if (buffer.empty()) {
            continue;
        }

        buffer.erase(remove(buffer.begin(), buffer.end(), '='), buffer.end());
        buffer.erase(remove(buffer.begin(), buffer.end(), '('), buffer.end());
        buffer.erase(remove(buffer.begin(), buffer.end(), ')'), buffer.end());
        buffer.erase(remove(buffer.begin(), buffer.end(), ','), buffer.end());

        stringstream ss(buffer);
        string map_node;
        string left_node;
        string right_node;
        ss >> map_node;
        ss >> left_node;
        ss >> right_node;

        if (map_node[2] == 'A') {
            starting_nodes.push_back(map_node);
            intervals.push_back(0);
        }

        std::pair<string, string> p{left_node, right_node};
        desert_map[map_node] = p;
	}

    uint64_t steps = 0;
    int instruction_size = instructions.size();

    while (!areNodesAtEnd(intervals)) {

        int i = 0;
        for (auto &node : starting_nodes) {
            if (instructions[steps % instruction_size] == 'L') {
                node = desert_map[node].first;
            } else {
                node = desert_map[node].second;
            }
            if (node[2] == 'Z') {
                intervals[i] = steps + 1;
            }
            i++;
        }
        
        steps++;
    }

    steps = 1;

    for (auto i : intervals) {
        steps = lcm(i, steps);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Total steps taken " << steps << " time taken " << duration.count() << " us" << endl;

	return 0;
}
