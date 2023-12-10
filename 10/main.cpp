#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
    int startingX = 0;
    int startingY = 0;
    int currentX = 0;
    int currentY = 0;
    int row = 0;
    // 1 left, 2 up, 3 right, 4 down
    int direction;

	while(getline(infile, buffer)) {
        map.push_back(buffer);
        size_t startPos = buffer.find('S');
        if (startPos != string::npos)  {
            startingX = startPos;
            startingY = row;
        }
        row++;
	}
    bool foundNext = false;

    // Check the next pipe around the starting point
    // Left from starting point
    if (startingX > 0) {
        char left = map.at(startingY)[startingX-1];
        if (left == '-' || left == 'L' || left == 'F') {
            currentX = startingX-1;
            currentY = startingY;
            foundNext = true;
            direction = 1;
        }
    }

    if (!foundNext && startingX < map.at(0).size()) {
        char right = map.at(startingY)[startingX+1];
        if (right == '-' || right == 'J' || right == '7') {
            currentX = startingX+1;
            currentY = startingY;
            foundNext = true;
            direction = 3;
        }
    }

    if (!foundNext && startingY > 0) {
        char up = map.at(startingY-1)[startingX];
        if (up == '|' || up == 'F' || up == '7') {
            currentX = startingX;
            currentY = startingY-1;
            foundNext = true;
            direction = 2;
        }
    }

    if (!foundNext && startingY < map.size()) {
        char down = map.at(startingY+1)[startingX];
        if (down == '|' || down == 'J' || down == 'L') {
            currentX = startingX;
            currentY = startingY+1;
            foundNext = true;
            direction = 4;
        }
    }

    int steps = 1;

    while (map.at(currentY)[currentX] != 'S') {
        char current = map.at(currentY)[currentX];

        switch(current) {
            case '|':
                if (direction == 2) {
                    currentY--;
                } else if (direction == 4) {
                    currentY++;
                }
                break;

            case '-':
                if (direction == 1) {
                    currentX--;
                } else if (direction == 3) {
                    currentX++;
                }
                break;
            
            case 'L':
                if (direction == 1) {
                    currentY--;
                    direction = 2;
                } else if (direction == 4) {
                    currentX++;
                    direction = 3;
                }
                break;
            
            case 'J':
                if (direction == 3) {
                    currentY--;
                    direction = 2;
                } else if (direction == 4) {
                    currentX--;
                    direction = 1;
                }
                break;
            
            case '7':
                if (direction == 3) {
                    currentY++;
                    direction = 4;
                } else if (direction == 2) {
                    currentX--;
                    direction = 1;
                }
                break;

            case 'F':
                if (direction == 1) {
                    currentY++;
                    direction = 4;
                } else if (direction == 2) {
                    currentX++;
                    direction = 3;
                }
                break;

        }
        steps++;
    }

    cout << "Farthest step is " << steps / 2 << " away" << endl;
}
