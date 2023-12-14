#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

uint32_t findMirrors(vector<string> &map) {

    for (auto s : map) {
        cout << s << endl;
    }

    // Find mirrors with exactly one smudge, first by columns
    uint32_t columns_to_left = 0;
    for (int i = 0; i < map.at(0).size(); i++) {
        bool mirror = true;
        uint32_t differences = 0;
        for (int j = 0; j < map.size(); j++) {
            if (map.at(j)[i] != map.at(j)[i+1]) {
                differences++;
            }
            if (differences > 1) {
                mirror = false;
            }
        }

        // If there is mirror, need to check all the other columns as well
        if (mirror) {
            int k = i+2;
            int l = i-1;
            while (l >= 0 && k < map.at(0).size()) {
                for (int j = 0; j < map.size(); j++) {
                    if (map.at(j)[l] != map.at(j)[k]) {
                        differences++;
                    }
                    if (differences > 1) {
                        mirror = false;
                    }
                }
                l--;
                k++;
            }
        }

        if (mirror && differences == 1) {
            columns_to_left = i + 1;
            cout << "Found vertical mirror with " << columns_to_left << " columns to left" << endl;
            break;
        }
    }


    uint32_t rows_above = 0;
    // Find mirrors, then by rows, no need to look last row
    for (int i = 0; i < map.size() - 1; i++) {
        bool mirror = true;
        uint32_t differences = 0;
        for (int j = 0; j < map.at(0).size(); j++) {
            if (map.at(i)[j] != map.at(i+1)[j]) {
                differences++;
            }
            if (differences > 1) {
                mirror = false;
            }
        }

        // If there is mirror, need to check all the other rows as well
        if (mirror) {
            int k = i+2;
            int l = i-1;
            while (l >= 0 && k < map.size()) {
                for (int j = 0; j < map.at(0).size(); j++) {
                    if (map.at(l)[j] != map.at(k)[j]) {
                        differences++;
                    }
                    if (differences > 1) {
                        mirror = false;
                    }
                }
                l--;
                k++;
            }
        }

        if (mirror && differences == 1) {
            rows_above += i + 1;
            cout << "Found horizontal mirror with " << rows_above << " rows above" << endl;
        }
    }

    return rows_above * 100 + columns_to_left;
}

int main()
{
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;

    uint64_t sum = 0;

    // Read galaxy map
	while(getline(infile, buffer)) {
        if (!buffer.empty()) {
            map.push_back(buffer);
        }

        if (buffer.empty() || infile.eof()) {
            cout << "End of map" << endl;
            sum += findMirrors(map);
            map.clear();
        }
	}

    cout << "Mirror sum " << sum << endl;

}
