#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct galaxy {
    int32_t x;
    int32_t y;
};

int main()
{
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
    vector<struct galaxy> galaxies;

    uint64_t sum_distance = 0;

    // Read galaxy map
	while(getline(infile, buffer)) {
        map.push_back(buffer);
	}

    cout << "Galaxy before " << endl;
    for (auto s : map) {
        cout << s << endl;
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
            for (int j = 0; j < map.size(); j++) {
                map.at(j).insert(i, ".");
            }
            i++;
        }
    }

    // Expand the universe, then expanding rows
    for (int i = 0; i < map.size(); i++) {
        // If there are no galaxies on row, expand the row
        if (map.at(i).find('#') == string::npos) {
            string s(map.at(i).size(), '.');
            auto it = map.begin() + i;
            map.insert(it, s);
            i++;
        }
    }

    cout << "Galaxy after" << endl;
    for (auto s : map) {
        cout << s << endl;
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

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            sum_distance += abs(galaxies.at(i).x - galaxies.at(j).x) + abs(galaxies.at(i).y - galaxies.at(j).y);
        }
    }

    cout << "Total sum of distances " << sum_distance << endl;

}
