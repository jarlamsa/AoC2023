#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    vector<string> map;
    vector<string> raymap;
    int startingX = 0;
    int startingY = 0;
    int currentX = 0;
    int currentY = 0;
    int row = 0;
    // 1 left, 2 up, 3 right, 4 down
    int direction;

	while(getline(infile, buffer)) {
        string dots(buffer.size(), '.');
        map.push_back(buffer);
        raymap.push_back(dots);
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

    raymap.at(currentY)[currentX] = 'P';
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
        raymap.at(currentY)[currentX] = 'P';
        steps++;
    }

    // Check all the tiles with dot and calculate how many path tiles there are in each direction
    row = 0;
    for (auto &s : raymap) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '.') {
                int count = 0;
                int crossing = 0;
                // Raycast left
                for (int j = i - 1; j >= 0; j--) {
                    if (s[j] == 'P') {
                        if ((map.at(row)[j] == '|' ))
                        {
                            count++;
                        } else if (map.at(row)[j] == '7') {
                            crossing = 1;
                        } else if (map.at(row)[j] == 'J') {
                            crossing = 2;
                        } else if (map.at(row)[j] == 'L') {
                            if (crossing == 1) {
                                count++;
                            }
                            crossing = 0;
                        } else if (map.at(row)[j] == 'F') {
                            if (crossing == 2) {
                                count++;
                            }
                            crossing = 0;
                        }

                    }
                }
                // If pairless, then it is outside
                if (count == 0 || count % 2 == 0) {
                    s[i] = 'O';
                    continue;
                }

                count = 0;
                crossing = 0;
                // Raycast right
                for (int j = i + 1; j < s.size(); j++) {
                    if (s[j] == 'P') {
                        if ((map.at(row)[j] == '|' ))
                        {
                            count++;
                        } else if (map.at(row)[j] == 'F') {
                            crossing = 1;
                        } else if (map.at(row)[j] == 'L') {
                            crossing = 2;
                        } else if (map.at(row)[j] == 'J') {
                            if (crossing == 1) {
                                count++;
                            }
                            crossing = 0;
                        } else if (map.at(row)[j] == '7') {
                            if (crossing == 2) {
                                count++;
                            }
                            crossing = 0;
                        }

                    }
                }

                // If pairless, then it is outside
                if (count == 0 || count % 2 == 0) {
                    s[i] = 'O';
                    continue;
                }

                count = 0;
                crossing = 0;
                // Raycast up
                for (int j = row-1; j >= 0; j--) {
                    if (raymap.at(j)[i] == 'P') {
                        if ((map.at(j)[i] == '-' ))
                        {
                            count++;
                        } else if (map.at(j)[i] == 'J') {
                            crossing = 1;
                        } else if (map.at(j)[i] == 'L') {
                            crossing = 2;
                        } else if (map.at(j)[i] == 'F') {
                            if (crossing == 1) {
                                count++;
                            }
                            crossing = 0;
                        } else if (map.at(j)[i] == '7') {
                            if (crossing == 2) {
                                count++;
                            }
                            crossing = 0;
                        }
                    }
                }

                // If pairless, then it is outside
                if (count == 0 || count % 2 == 0) {
                    s[i] = 'O';
                    continue;
                }

                count = 0;
                // Raycast down
                for (int j = row+1; j < raymap.size(); j++) {
                    if (raymap.at(j)[i] == 'P') {
                        if ((map.at(j)[i] == '-' ))
                        {
                            count++;
                        } else if (map.at(j)[i] == '7') {
                            crossing = 1;
                        } else if (map.at(j)[i] == 'F') {
                            crossing = 2;
                        } else if (map.at(j)[i] == 'L') {
                            if (crossing == 1) {
                                count++;
                            }
                            crossing = 0;
                        } else if (map.at(j)[i] == 'J') {
                            if (crossing == 2) {
                                count++;
                            }
                            crossing = 0;
                        }
                    }
                }

                // If pairless, then it is outside
                if (count == 0 || count % 2 == 0) {
                    s[i] = 'O';
                    continue;
                }

                s[i] = 'I';
            }
        }
        row++;
    }

    int inCount = 0;

    for (auto s : raymap) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'I') {
                inCount++;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Number of tiles inside area " << inCount << " time taken " << duration.count() << " us" << endl;

}
