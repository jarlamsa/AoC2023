#include <iostream>

using namespace std;


int main()
{
    int times[4] = {52, 94, 75, 94};
    int distances[4] = {426, 1374, 1279, 1216};

    int numMultiplied = 1;

    for (int i = 0; i < 4; i++) {
        int waysToWin = 0;
        for (int j = 1; j < times[i]; j++) {
            if ((times[i] - j) * j > distances[i]) {
                waysToWin++;
            }
        }

        numMultiplied *= waysToWin;
    }

    cout << "Result " << numMultiplied << endl;

	return 0;
}
