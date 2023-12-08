#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
	ifstream infile("input.txt");
	string buffer;
    std::map<std::string, std::pair<string, string>> desert_map;
    string instructions;

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

        std::pair<string, string> p{left_node, right_node};
        desert_map[map_node] = p;
	}

    string starting_location = "AAA";
    string ending_location = "ZZZ";

    string current_node = starting_location;
    int steps = 0;
    int instruction_size = instructions.size();

    while (current_node != ending_location) {
        if (instructions[steps % instruction_size] == 'L') {
            current_node = desert_map[current_node].first;
        } else {
            current_node = desert_map[current_node].second;
        }

        steps++;
    }

    cout << "Total steps taken " << steps << endl;

	return 0;
}
