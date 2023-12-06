#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
    uint64_t time = 52947594;
    uint64_t maxDistance = 426137412791216;

    uint64_t waysToWin = 0;
    uint64_t firstWinningTime = 0;
    uint64_t lastWinningTime = 0;

    // Calculate the minimum speed to begin with
    uint64_t minSpeed = maxDistance / time;

    // Find first winning time
    for (uint64_t j = minSpeed; j < time; j++) {
        if ((time - j) * j > maxDistance) {
            firstWinningTime = j;
            break;
        }
    }

    // Find last winning time
    for (uint64_t j = time - minSpeed; j > 0; j--) {
        if ((time - j) * j > maxDistance) {
            lastWinningTime = j;
            break;
        }
    }

    waysToWin = lastWinningTime - firstWinningTime + 1;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Ways to win: " << waysToWin << " time spent " << duration.count() << " us" << endl;

	return 0;
}
