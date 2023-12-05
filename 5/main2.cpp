#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct conversion_range {
    int64_t destination_start;
    int64_t destination_end;
    int64_t source_start;
    int64_t source_end;
    int step;
};

struct seed_range {
    int64_t start_value;
    int64_t end_value;
    int64_t step;
};

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    int conversionStep = 0;
    vector<seed_range> seeds;
    seeds.reserve(20000);
    vector<conversion_range> conversions;

	while(getline(infile, buffer)) {
        // First line contains seeds
        size_t pos = 0;
        size_t endpos = 0;
        if (seeds.empty()) {
            while (pos != string::npos) {
                int64_t num_of_seeds = 0;
                int64_t starting_number = 0;
                pos = buffer.find_first_of("1234567890", pos);
                endpos = buffer.find_first_not_of("1234567890", pos);
                if (endpos == string::npos) {
                    starting_number = stol(buffer.substr(pos));
                } else {
                    starting_number = stol(buffer.substr(pos, endpos - pos));
                }

                pos = endpos;

                pos = buffer.find_first_of("1234567890", pos);
                endpos = buffer.find_first_not_of("1234567890", pos);
                if (endpos == string::npos) {
                    num_of_seeds = stol(buffer.substr(pos));
                } else {
                    num_of_seeds = stol(buffer.substr(pos, endpos - pos));
                }

                struct seed_range aseed;
                aseed.start_value = starting_number;
                aseed.end_value = starting_number + num_of_seeds - 1;
                aseed.step = 0;
                seeds.push_back(aseed);

                pos = endpos;
            }
        } else {
            // Any line that starts with number is a conversion line
            pos = buffer.find_first_of("1234567890");
            if (pos == string::npos) {
                pos = buffer.find_first_of(":");
                if (pos != string::npos) {
                    conversionStep++;
                }
                continue;
            }

            struct conversion_range range;

            endpos = buffer.find_first_of(" ", pos);
            range.destination_start = stol(buffer.substr(pos, endpos - pos));

            pos = buffer.find_first_of("1234567890", endpos);
            endpos = buffer.find_first_of(" ", pos);
            range.source_start = stol(buffer.substr(pos, endpos - pos));

            pos = buffer.find_first_of("1234567890", endpos);
            int64_t num = stol(buffer.substr(pos));
            range.destination_end = range.destination_start + num - 1;
            range.source_end = range.source_start + num - 1;
            range.step = conversionStep;
            conversions.push_back(range);
        }
	}

    for (int i = 0; i < seeds.size(); i++) {
        struct seed_range &s = seeds.at(i);
        for (auto conv : conversions) {
            if (conv.step > s.step) {
                // seeds fully in range
                if (s.start_value >= conv.source_start && s.end_value <= conv.source_end) {
                    s.start_value = s.start_value - conv.source_start + conv.destination_start;
                    s.end_value = s.end_value - conv.source_start + conv.destination_start;
                    s.step = conv.step;
                    continue;
                }

                // beginning of seeds in range
                if (s.start_value >= conv.source_start && s.start_value <= conv.source_end && s.end_value > conv.source_end) {
                    // convert the beginning of range, make a new range of the rest and place it to the end of seeds
                    struct seed_range aseed;
                    aseed.start_value = conv.source_end + 1;
                    aseed.end_value = s.end_value;
                    aseed.step = s.step;
                    seeds.push_back(aseed);

                    s.start_value = s.start_value - conv.source_start + conv.destination_start;
                    s.end_value = conv.destination_end;
                    s.step = conv.step;
                    continue;
                }

                // end of seeds in range
                if (s.start_value < conv.source_start && s.end_value >= conv.source_start && s.end_value <= conv.source_end) {
                    struct seed_range aseed;
                    aseed.start_value = s.start_value;
                    aseed.end_value = conv.source_start - 1;
                    aseed.step = s.step;
                    seeds.push_back(aseed);

                    s.start_value = conv.destination_start;
                    s.end_value = s.end_value - conv.source_start + conv.destination_start;
                    s.step = conv.step;
                    continue;
                }

                // middle of seeds in range
                if (s.start_value < conv.source_start && s.end_value > conv.source_end) {
                    struct seed_range aseed;
                    aseed.start_value = s.start_value;
                    aseed.end_value = conv.source_start - 1;
                    aseed.step = s.step;
                    seeds.push_back(aseed);

                    struct seed_range bseed;
                    bseed.start_value = conv.source_end + 1;
                    bseed.end_value = s.end_value;
                    bseed.step = s.step;
                    seeds.push_back(bseed);

                    s.start_value = conv.destination_start;
                    s.end_value = conv.destination_end;
                    s.step = conv.step;
                    continue;
                }
            }
        }
    }

    int64_t min_seed_location = 0;

    for (auto s : seeds) {
        if (min_seed_location == 0 || s.start_value < min_seed_location) {
            min_seed_location = s.start_value;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Minimum seed location " << min_seed_location << " time taken " << duration.count() << " us" << endl;
	return 0;
}
