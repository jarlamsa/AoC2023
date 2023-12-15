#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct label {
    string label;
    uint32_t hash;
    uint32_t focal_length;
    // 0 remove, 1 add/replace
    uint32_t operation;
};

struct box {
    vector<struct label> labels;
};

uint32_t hashAlgorithm(string seq)
{
    uint32_t value = 0;
    //cout << "Hashing sequence " << seq << endl;
    for (int i = 0; i < seq.size(); i++) {
        value += (uint32_t)seq[i];
        value *= 17;
        value = value % 256;
    }

    //cout << "Hashed sequence becomes " << value << endl;
    return value;
}

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    vector<string> sequences;
    struct box boxlist[256];

    uint64_t sum = 0;

    // Read galaxy map
	while(getline(infile, buffer)) {
        stringstream ss(buffer);
        string step;
        
        while (getline(ss, step, ',')) {
            size_t pos = step.find_first_of("=-");
            struct label lab;
            lab.label = step.substr(0, pos);
            if (step[pos] == '-') {
                lab.operation = 0;
            } else {
                lab.operation = 1;
                lab.focal_length = stoi(step.substr(pos+1));
            }
            lab.hash = hashAlgorithm(lab.label);
            //cout << "Read label " << lab.label << " hash value of " << lab.hash << " operation " << lab.operation << " focal length " << lab.focal_length << endl;
            bool found = false;
            for (auto it = boxlist[lab.hash].labels.begin(); it != boxlist[lab.hash].labels.end(); it++) {
                if ((*it).label == lab.label) {
                    found = true;
                    if (lab.operation == 0) {
                        boxlist[lab.hash].labels.erase(it);
                    } else {
                        (*it).focal_length = lab.focal_length;
                    }
                    break;
                }
            }

            if (!found && lab.operation == 1) {
                boxlist[lab.hash].labels.push_back(lab);
            }
        }
	}

    for (int i = 0; i < 256; i++) {
        if (boxlist[i].labels.size() > 0) {
            int j = 1;
            for (auto l : boxlist[i].labels) {
                sum += (i+1) * (j) * l.focal_length;
                j++;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Sum of focusing power " << sum << " time taken " << duration.count() << " us" << endl;

}
