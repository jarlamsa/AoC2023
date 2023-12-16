#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Directions: 1 up, 2 left, 3 down, 4 right
void followBeam(vector<string> &map, vector<string> &energized, int direction, int row, int col)
{
    int current_row = row;
    int current_col = col;
    int current_dir = direction;

    switch (map.at(current_row)[current_col]) {
        case '/':
            if (current_dir == 1) {
                current_dir = 4;
            } else if (current_dir == 2) {
                current_dir = 3;
            } else if (current_dir == 3) {
                current_dir = 2;
            } else if (current_dir == 4) {
                current_dir = 1;
            }
            break;
        case '\\':
            if (current_dir == 1) {
                current_dir = 2;
            } else if (current_dir == 2) {
                current_dir = 1;
            } else if (current_dir == 3) {
                current_dir = 4;
            } else if (current_dir == 4) {
                current_dir = 3;
            }
            break;
    }

    while (current_row >= 0 && current_row < map.size() && current_col >= 0 && current_col < map.at(0).size() ) {
        if (energized.at(current_row)[current_col] == '.') {
            energized.at(current_row)[current_col] = '#';
        }
        switch(current_dir) {
            case 1:
                current_row--;
                break;
            case 2:
                current_col--;
                break;
            case 3:
                current_row++;
                break;
            case 4:
                current_col++;
                break;
        }

        // Check the current tile if we need to change direction or split
        if (current_row >= 0 && current_row < map.size() && current_col >= 0 && current_col < map.at(0).size()) {
            switch (map.at(current_row)[current_col]) {
                case '/':
                    if (current_dir == 1) {
                        current_dir = 4;
                    } else if (current_dir == 2) {
                        current_dir = 3;
                    } else if (current_dir == 3) {
                        current_dir = 2;
                    } else if (current_dir == 4) {
                        current_dir = 1;
                    }
                    break;
                case '\\':
                    if (current_dir == 1) {
                        current_dir = 2;
                    } else if (current_dir == 2) {
                        current_dir = 1;
                    } else if (current_dir == 3) {
                        current_dir = 4;
                    } else if (current_dir == 4) {
                        current_dir = 3;
                    }
                    break;
                case '-':
                    if (current_dir == 1 || current_dir == 3) {
                        current_dir = 2;
                        // SPLIT HERE TO RIGHT
                        // Check if we have used this split earlier or not
                        if (energized.at(current_row)[current_col] != '&') {
                            energized.at(current_row)[current_col] = '&';
                            followBeam(map, energized, 4, current_row, current_col);
                        } else {
                            return;
                        }
                    }
                    break;
                case '|':
                    if (current_dir == 2 || current_dir == 4) {
                        current_dir = 1;
                        // SPLIT HERE TO DOWN
                        if (energized.at(current_row)[current_col] != '&') {
                            energized.at(current_row)[current_col] = '&';
                            followBeam(map, energized, 3, current_row, current_col);
                        } else {
                            return;
                        }
                    }
                    break;
            }
        }
    }
}

uint32_t countEnergized(vector<string> energized)
{
    uint32_t sum = 0;
    for (auto s : energized) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '&' || s[i] == '#') {
                sum++;
            }
        }
    }
    return sum;
}

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
    vector<string> energized;

    uint32_t sum = 0;

	while(getline(infile, buffer)) {
        string dots(buffer.size(), '.');
        map.push_back(buffer);
        energized.push_back(dots);
	}

    followBeam(map, energized, 4, 0, 0);
    sum = countEnergized(energized);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Sum of energized tiles " << sum << " time taken " << duration.count() << " us" << endl;

}
