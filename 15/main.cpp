#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

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
	ifstream infile("input.txt");
	string buffer;
    vector<string> sequences;

    uint64_t sum = 0;

    // Read galaxy map
	while(getline(infile, buffer)) {
        stringstream ss(buffer);
        string step;
        
        while (getline(ss, step, ',')) {
            sequences.push_back(step);
        }
	}

    for (auto seq : sequences) {
        sum += hashAlgorithm(seq);
    }

    cout << "Sum of hashed sequences " << sum << endl;

}
