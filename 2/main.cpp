#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	ifstream infile("input.txt");
	string buffer;

    int maxRed = 12;
    int maxGreen = 13;
    int maxBlue = 14;

    int possibleGames = 0;
    // Start straight from game 1, input is organized
    int game = 1;

	while(getline(infile, buffer)) {
        bool possible = true;
        size_t pos = buffer.find(':');
        vector<string> rounds;
        stringstream stream(buffer.substr(pos + 1));
        string round;

        while (getline(stream, round, ';')) {
            rounds.push_back(round);
        }

        // Loop all the rounds
        for(string set : rounds) {
            int reds = 0;
            int greens = 0;
            int blues = 0;
            stringstream cubestream(set);
            string cubes;

            while (getline(cubestream, cubes, ',')) {
                int amount = 0;
                // Remove preceding space
                cubes.erase(0, cubes.find_first_not_of(' '));
                size_t count_pos = cubes.find(' ');
                
                amount = stoi(cubes.substr(0, count_pos));

                if (cubes.find("red") != string::npos) {
                    reds += amount;
                } else if (cubes.find("green") != string::npos) {
                    greens += amount;
                } else if (cubes.find("blue") != string::npos) {
                    blues += amount;
                } else {
                    cout << "Erroneus color cubes" << endl;
                }
            }

            if (reds > maxRed || greens > maxGreen || blues > maxBlue) {
                possible = false;
                break;
            }
        }

        if (possible) {
            cout << "Game number " << game << " was possible" << endl;
            possibleGames += game;
        }
        game++;
	}

	cout << "Possible games: " << possibleGames << endl;

	return 0;
}
