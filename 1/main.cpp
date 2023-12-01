#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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

        // Tens
        calibrationValue = stoi(buffer.substr(firstPart, 1)) * 10;
        // Ones
        calibrationValue += stoi(buffer.substr(secondPart, 1));
        cout << "Calibration Value: " << calibrationValue << endl;
        calibrationSum += calibrationValue;
	}

	cout << "Calibration Sum: " << calibrationSum << endl;

	return 0;
}
