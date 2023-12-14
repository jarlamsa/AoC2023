#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	ifstream infile("input.txt");
	string buffer;
    vector<string> rock_map;

    uint64_t sum_distance = 0;

    // Read galaxy map
	while(getline(infile, buffer)) {
        rock_map.push_back(buffer);
	}

    cout << "Rocks" << endl;
    for (auto s : rock_map) {
        cout << s << endl;
    }

    // Tilt the board
    for (int i = 1; i < rock_map.size(); i++) {
        for (int j = 0; j < rock_map.at(i).size(); j++) {
            if (rock_map.at(i)[j] == 'O') {
                // Find the place to swap the rock if it can move
                if (rock_map.at(i-1)[j] != '.') {
                    continue;
                }

                int swap_row = i-2;

                while(swap_row >= 0) {
                    if (rock_map.at(swap_row)[j] != '.') {
                        break;
                    }
                    swap_row--;
                }

                swap_row++;

                rock_map.at(i)[j] = '.';
                rock_map.at(swap_row)[j] = 'O';
            }
        }
    }

    cout << endl << "Tilted" << endl;
    for (auto s : rock_map) {
        cout << s << endl;
    }

    uint64_t sum = 0;
    uint32_t multiplier = rock_map.size();
    cout << "Multiplier in the start " << multiplier << endl;

    for (auto s : rock_map) {
        uint32_t rocks = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'O') {
                rocks++;
            }
        }
        sum += multiplier * rocks;
        multiplier--;
    }

    cout << "Sum in the end " << sum << endl;
}
