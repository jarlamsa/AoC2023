#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct conversion_range {
    uint64_t destination_range;
    uint64_t source_range;
    uint64_t range_length;
    int step;
};

struct seed {
    uint64_t seed_value;
    int step;
};

int main()
{
	ifstream infile("input.txt");
	string buffer;
    int sumValue = 0;
    int conversionStep = 0;
    vector<seed> seeds;
    vector<conversion_range> conversions;

	while(getline(infile, buffer)) {
        // First line contains seeds
        size_t pos = 0;
        size_t endpos = 0;
        if (seeds.empty()) {
            while (pos != string::npos) {
                struct seed aseed;
                pos = buffer.find_first_of("1234567890", pos);
                endpos = buffer.find_first_not_of("1234567890", pos);
                if (endpos == string::npos) {
                    aseed.seed_value = stol(buffer.substr(pos));
                } else {
                    aseed.seed_value = stol(buffer.substr(pos, endpos - pos));
                }

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
            range.destination_range = stol(buffer.substr(pos, endpos - pos));

            pos = buffer.find_first_of("1234567890", endpos);
            endpos = buffer.find_first_of(" ", pos);
            range.source_range = stol(buffer.substr(pos, endpos - pos));

            pos = buffer.find_first_of("1234567890", endpos);
            range.range_length = stol(buffer.substr(pos));
            range.step = conversionStep;
            conversions.push_back(range);
        }
	}

    for (struct seed& s : seeds) {
        for (auto conv : conversions) {
            if (conv.step > s.step) {
                if (s.seed_value >= conv.source_range && s.seed_value < conv.source_range + conv.range_length) {
                    s.seed_value = s.seed_value - conv.source_range + conv.destination_range;
                    s.step = conv.step;
                }
            }
        }
    }

    uint64_t min_seed_location = 0;

    for (auto s : seeds) {
        if (min_seed_location == 0 || s.seed_value < min_seed_location) {
            min_seed_location = s.seed_value;
        }
    }

    cout << "Minimum seed location " << min_seed_location << endl;

	return 0;
}
