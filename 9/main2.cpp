#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    int64_t extrapolated_sum = 0;
    

	while(getline(infile, buffer)) {
        vector<vector<int64_t>> oasis_report;
        vector<int64_t> initial_line;
        bool zeroed = false;
        int64_t element;
        stringstream ss(buffer);
        while (ss >> element) {
            initial_line.push_back(element);
        }

        oasis_report.push_back(initial_line);
        while (!zeroed) {
            zeroed = true;
            vector<int64_t> latest = oasis_report.back();
            vector<int64_t> newline;

            int64_t first = latest.at(0);

            for (int i = 1; i < latest.size(); i++) {
                int64_t second = latest.at(i);
                int64_t difference = second - first;

                if (difference != 0) {
                    zeroed = false;
                }
                newline.push_back(difference);
                first = second;
            }
            oasis_report.push_back(newline);
        }

        int64_t extrapolated_value = 0;
        // Extrapolate
        for (auto itr = oasis_report.rbegin(); itr != oasis_report.rend(); itr++) {
            vector<int64_t> line = *itr;
            int64_t front = line.front();
            line.insert(line.begin(), front - extrapolated_value);
            extrapolated_value = line.front();
        }

        extrapolated_sum += extrapolated_value;
	}

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Sum of extrapolated values " << extrapolated_sum << " time taken " << duration.count() << " us" << endl;

}
