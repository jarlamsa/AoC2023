#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	ifstream infile("input.txt");
	string buffer;
    int sumValue = 0;

	while(getline(infile, buffer)) {
        vector<int> winningNumbers;
        vector<int> numbers;
        int cardValue = 0;
        //Find first semicolon, after that are winning numbers
        size_t pos = buffer.find_first_of(':') + 1;
        pos = buffer.find_first_not_of(" ", pos);
        bool winningNumber = true;

        while (pos != string::npos) {
            //If we get a part number, check how long it is
            if (isdigit(buffer[pos])) {
                int number = 0;
                size_t endpos = buffer.find_first_not_of("0123456789", pos);
                if (endpos == string::npos) {
                    number = stoi(buffer.substr(pos));
                } else {
                    number = stoi(buffer.substr(pos, endpos - pos));
                }

                if (winningNumber == true) {
                    winningNumbers.push_back(number);
                } else {
                    numbers.push_back(number);
                }
                pos = endpos;
            } else {
                // This would be a |
                winningNumber = false;
                pos++;
            }

            pos = buffer.find_first_not_of(" ", pos);
        }

        for (auto number : numbers) {
            for (auto winner : winningNumbers) {
                if (number == winner) {
                    if (cardValue == 0) {
                        cardValue++;
                    } else {
                        cardValue <<= 1;
                    }
                }
            }
        }
        sumValue += cardValue;
	}

    cout << "Sum of card values " << sumValue << endl;

	return 0;
}
