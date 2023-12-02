#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	ifstream infile("input.txt");
	string buffer;

    // Start straight from game 1, input is organized
    int game = 1;

    int powerSum = 0;

	while(getline(infile, buffer)) {
        size_t pos = buffer.find(':');
        vector<string> rounds;
        stringstream stream(buffer.substr(pos + 1));
        string round;
        int gamePower = 0;

        while (getline(stream, round, ';')) {
            rounds.push_back(round);
        }

        int minReds = 0;
        int minGreens = 0;
        int minBlues = 0;
        // Loop all the rounds
        for(string set : rounds) {
            stringstream cubestream(set);
            string cubes;

            while (getline(cubestream, cubes, ',')) {
                int amount = 0;
                // Remove preceding space
                cubes.erase(0, cubes.find_first_not_of(' '));
                size_t count_pos = cubes.find(' ');
                
                amount = stoi(cubes.substr(0, count_pos));

                if (cubes.find("red") != string::npos) {
                    if (amount > minReds) minReds = amount;
                } else if (cubes.find("green") != string::npos) {
                    if (amount > minGreens) minGreens = amount;
                } else if (cubes.find("blue") != string::npos) {
                    if (amount > minBlues) minBlues = amount;
                } else {
                    cout << "Erroneus color cubes" << endl;
                }
            }
        }
        cout << "Reds " << minReds << " Greens " << minGreens << " Blues " << minBlues << endl;
        gamePower = minReds * minGreens * minBlues;
        powerSum += gamePower;
	}

	cout << "Power sum: " << powerSum << endl;

	return 0;
}
