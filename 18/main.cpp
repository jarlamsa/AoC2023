#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct dig {
    int direction;
    int amount;
};

void floodFill(vector<string> &map, int row, int col)
{
    if (row < 0 || row >= map.size() || col < 0 || col >= map.at(0).size())
        return;
    
    if (map.at(row)[col] == '#')
        return;

    map.at(row)[col] = '#';
    floodFill(map, row+1, col);
    floodFill(map, row-1, col);
    floodFill(map, row, col+1);
    floodFill(map, row, col-1);
}

// Directions: 1 up, 2 left, 3 down, 4 right
int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
    vector<struct dig> dig_plan;

    uint32_t sum = 0;

	while(getline(infile, buffer)) {
        string dots(buffer.size(), '.');
        stringstream ss(buffer);
        struct dig d;
        string direction;
        ss >> direction;
        ss >> d.amount;

        if (direction == "U") {
            d.direction = 1;
        } else if (direction == "L") {
            d.direction = 2;
        } else if (direction == "D") {
            d.direction = 3;
        } else if (direction == "R") {
            d.direction = 4;
        }
        dig_plan.push_back(d);
	}

    // Check boundaries for map
    int32_t max_row = 0;
    int32_t max_col = 0;
    int32_t min_row = 0;
    int32_t min_col = 0;

    int32_t cur_row = 0;
    int32_t cur_col = 0;

    for (auto d : dig_plan) {
        if (d.direction == 1) {
            cur_row -= d.amount;
        } else if (d.direction == 2) {
            cur_col -= d.amount;
        } else if (d.direction == 3) {
            cur_row += d.amount;
        } else if (d.direction == 4) {
            cur_col += d.amount;
        }

        max_row = max(max_row, cur_row);
        max_col = max(max_col, cur_col);
        min_row = min(min_row, cur_row);
        min_col = min(min_col, cur_col);
    }

    for (int i = 0; i < max_row - min_row + 1; i++) {
        string dots(max_col - min_col + 1, '.');
        map.push_back(dots);
    }

    cur_row = abs(min_row);
    cur_col = abs(min_col);

    for (auto &d : dig_plan) {
        if (d.direction == 1) {
            for (int i = 0; i < d.amount; i++) {
                map.at(cur_row)[cur_col] = '#';
                cur_row--;
            }
        } else if (d.direction == 2) {
            for (int i = 0; i < d.amount; i++) {
                map.at(cur_row)[cur_col] = '#';
                cur_col--;
            }
        } else if (d.direction == 3) {
            for (int i = 0; i < d.amount; i++) {
                map.at(cur_row)[cur_col] = '#';
                cur_row++;
            }
        } else if (d.direction == 4) {
            for (int i = 0; i < d.amount; i++) {
                map.at(cur_row)[cur_col] = '#';
                cur_col++;
            }
        }
    }

    // Flood fill
    floodFill(map, abs(min_row-1), abs(min_col-1));

    cout << "Printing dig map" << endl;
    for (auto s : map) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '#') {
                sum++;
            }
        }
        cout << s << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Lava pool size " << sum << " time taken " << duration.count() << " us" << endl;

}
