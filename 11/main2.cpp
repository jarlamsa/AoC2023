#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct galaxy {
    int32_t x;
    int32_t y;
};

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
    vector<struct galaxy> galaxies;
    vector<int32_t> vertical_expansions;
    vector<int32_t> horizontal_expansions;

    uint64_t sum_distance = 0;

    // Read galaxy map
	while(getline(infile, buffer)) {
        map.push_back(buffer);
	}

    // Expand the universe, first expand columns
    for (int i = 0; i < map.at(0).size(); i++) {
        
        bool empty_column = true;
        for (int j = 0; j < map.size(); j++) {
            if (map.at(j)[i] == '#') {
                empty_column = false;
                break;
            }
        }

        if (empty_column) {
            vertical_expansions.push_back(i);
        }
    }

    // Expand the universe, then expanding rows
    for (int i = 0; i < map.size(); i++) {
        
        // If there are no galaxies on row, expand the row
        if (map.at(i).find('#') == string::npos) {
            horizontal_expansions.push_back(i);
        }
    }

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(0).size(); j++) {
            if (map.at(i)[j] == '#') {
                struct galaxy g;
                g.x = j;
                g.y = i;
                galaxies.push_back(g);
            }
        }
    }

    for (auto &g : galaxies) {
        int expansions = 0;
        for (auto h : horizontal_expansions) {
            if (g.y > h) {
                expansions++;
            }
        }

        g.y += (expansions * 999999);
        expansions = 0;
        for (auto v : vertical_expansions) {
            if (g.x > v) {
                expansions++;
            }
        }
        g.x += (expansions * 999999);
    }

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            sum_distance += abs(galaxies.at(i).x - galaxies.at(j).x) + abs(galaxies.at(i).y - galaxies.at(j).y);
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Total sum of distances " << sum_distance << " time taken " << duration.count() << " us" << endl;

}
