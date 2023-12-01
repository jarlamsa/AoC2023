#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string numbers[9] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

int main()
{
	ifstream infile("input.txt");
	string buffer;


    int calibrationSum = 0;

	while(getline(infile, buffer)) {
        cout << buffer << endl;
        int calibrationValue = 0;
        size_t firstPart = buffer.find_first_of("0123456789");
        size_t secondPart = buffer.find_last_of("0123456789");

        size_t foundPos = firstPart;

        for (int i = 0; i < 9; i++) {
            // Find any preceding written numbers
            size_t pos = buffer.find(numbers[i]);

            if (pos < foundPos && pos != string::npos) {
                foundPos = pos;
                calibrationValue = (i+1)*10;
            }
        }

        // No preceding written numbers found
        if (calibrationValue == 0) {
            // Tens
            calibrationValue = stoi(buffer.substr(firstPart, 1)) * 10;
        }

        foundPos = secondPart;
        int writtenNumber = 0;
        for (int i = 0; i < 9; i++) {
            // Reverse find any written numbers in the end of buffer
            size_t pos = buffer.rfind(numbers[i]);

            if (pos != string::npos && pos > foundPos) {
                foundPos = pos;
                writtenNumber = i+1;
            }
        }

        // No written numbers found in the end
        if (writtenNumber == 0) {
            // Ones
            calibrationValue += stoi(buffer.substr(secondPart, 1));
        } else {
            calibrationValue += writtenNumber;
        }

        calibrationSum += calibrationValue;
	}

	cout << "Calibration Sum: " << calibrationSum << endl;

	return 0;
}
