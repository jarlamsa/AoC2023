#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void spinBoard(vector<string> &rock_map)
{
    // Tilt the board north
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

    // Then tilt west
    for (auto &s : rock_map) {
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == 'O') {
                if (s[i-1] != '.') {
                    continue;
                }

                int swap_col = i-2;
                while (swap_col >= 0) {
                    if (s[swap_col] != '.') {
                        break;
                    }
                    swap_col--;
                }
                swap_col++;
                s[i] = '.';
                s[swap_col] = 'O';
            }
        }
    }
    // Then tilt south
    for (int i = rock_map.size()-2; i >= 0; i--) {
        for (int j = 0; j < rock_map.at(i).size(); j++) {
            if (rock_map.at(i)[j] == 'O') {
                // Find the place to swap the rock if it can move
                if (rock_map.at(i+1)[j] != '.') {
                    continue;
                }

                int swap_row = i+2;

                while(swap_row < rock_map.size()) {
                    if (rock_map.at(swap_row)[j] != '.') {
                        break;
                    }
                    swap_row++;
                }

                swap_row--;

                rock_map.at(i)[j] = '.';
                rock_map.at(swap_row)[j] = 'O';
            }
        }
    }
    // Then tilt east
    for (auto &s : rock_map) {
        for (int i = s.size() - 2; i >= 0; i--) {
            if (s[i] == 'O') {
                if (s[i+1] != '.') {
                    continue;
                }

                int swap_col = i+2;
                while (swap_col < s.size()) {
                    if (s[swap_col] != '.') {
                        break;
                    }
                    swap_col++;
                }
                swap_col--;
                s[i] = '.';
                s[swap_col] = 'O';
            }
        }
    }
}

uint64_t calculateLoad(vector<string> &rock_map)
{
    uint64_t sum = 0;
    uint32_t multiplier = rock_map.size();

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

    return sum;
}

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    vector<string> rock_map;
    vector<uint64_t> loads;

    uint64_t sum_distance = 0;

    // Read galaxy map
	while(getline(infile, buffer)) {
        rock_map.push_back(buffer);
	}

    // Spin the board 100 times, it is stabilized at that point and record the loads to see when the pattern starts recurring
    for (int i = 1; i < 100; i++) {
        spinBoard(rock_map);
    }
    uint64_t current_load = calculateLoad(rock_map);
    uint64_t new_load = 0;
    // Record loads and check when the 100th load is back
    do {
        spinBoard(rock_map);
        new_load = calculateLoad(rock_map);
        loads.push_back(new_load);
    } while(current_load != new_load);

    uint64_t billionth = loads.at((1000000000 - 100) % loads.size() );

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Load after billionth cycle " << billionth << " time taken " << duration.count() << " us" << endl;
}
