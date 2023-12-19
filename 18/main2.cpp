#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct dig {
    int64_t direction = 0;
    int64_t amount = 0;
};

// NOTE: input uses different directions than was used in first part
// Directions: 0 right, 1 down, 2 left, 3 up
int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    vector<pair<int64_t, int64_t>> vertices;
    vector<struct dig> dig_plan;

    uint32_t sum = 0;

	while(getline(infile, buffer)) {
        string dots(buffer.size(), '.');
        stringstream ss(buffer);
        struct dig d;
        string a, b;
        ss >> a;
        ss >> b;
        string hex;
        ss >> hex;

        d.amount = stoi(hex.substr(2,5), nullptr, 16);
        d.direction = stoi(hex.substr(7,1));

        dig_plan.push_back(d);
	}

    int32_t cur_row = 0;
    int32_t cur_col = 0;

    int64_t routearea = 0;

    for (auto d : dig_plan) {
        if (d.direction == 0) {
            cur_col += d.amount;
        } else if (d.direction == 1) {
            cur_row += d.amount;
        } else if (d.direction == 2) {
            cur_col -= d.amount;
        } else if (d.direction == 3) {
            cur_row -= d.amount;
        }
        pair<int, int> v;
        v.first = cur_col;
        v.second = cur_row;
        vertices.push_back(v);
        routearea += d.amount;
    }

    for (auto v : vertices) {
        cout << v.first << ", " << v.second << endl;
    }

    int64_t area = 0;
    
    int j = vertices.size() - 1;

    for (int i = 0; i < vertices.size(); i++) {
        area += (vertices[j].first + vertices[i].first) * (vertices[j].second - vertices[i].second);
        j = i;
    }

    area = abs(area);
    area += routearea;
    area /= 2;
    area++;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Lava pool size " << area << " time taken " << duration.count() << " us" << endl;

}
