#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <climits>
#include <queue>
#include <iomanip>

using namespace std;
using namespace std::chrono;

#define MAP_SIZE 141

struct node {
	int row;
	int col;
	int distance = INT_MAX;
	int direction = 0;
	int moved = 0;
};

struct node_comp {
	bool operator()(struct node const& n1, struct node const& n2)
	{
		return n1.distance > n2.distance;
	}
};

int main()
{
    auto start = high_resolution_clock::now();
	ifstream infile("input.txt");
	string buffer;
    int map[MAP_SIZE][MAP_SIZE] = {0};
	int distance[MAP_SIZE][MAP_SIZE][5][4];
	bool visited[MAP_SIZE][MAP_SIZE][5][4] = {false};
	priority_queue<struct node, vector<struct node>, node_comp> Q;
	int i = 0;

	while(getline(infile, buffer)) {
		for(int j = 0; j < buffer.size(); j++) {
			map[i][j] = buffer.at(j) - '0';
			//distance[i][j] = INT_MAX;
			struct node n;
			n.row = i;
			n.col = j;
			if (i == 0 && j == 0) {
				n.distance = 0;
				Q.push(n);
			}
		}
		i++;
	}

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l < 4; l++) {
					if (i == 0 && j == 0) {
						distance[i][j][k][l] = 0;
					} else {
						distance[i][j][k][l] = INT_MAX;
					}
				}
			}
		}
	}

	// 1 up, 2 left, 3 down, 4 right, 0 not moved yet
	uint32_t moved = 0;

	while (!Q.empty()) {
		struct node n = Q.top();
		Q.pop();
		visited[n.row][n.col][n.direction][n.moved] = true;

		// Check up
		if (n.row > 0 && n.direction != 3) {
			if ((n.direction == 1 && n.moved < 3) || n.direction != 1) {
				if (n.direction == 1) {
					moved = n.moved + 1;
				} else {
					moved = 1;
				}
				if (!visited[n.row-1][n.col][1][moved] && n.distance + map[n.row-1][n.col] < distance[n.row-1][n.col][1][moved]) {
					distance[n.row-1][n.col][1][moved] = n.distance + map[n.row-1][n.col];
					struct node p;
					p.row = n.row-1;
					p.col = n.col;
					p.distance = n.distance + map[n.row-1][n.col];
					p.direction = 1;
					p.moved = moved;
					Q.push(p);
				}
			}
		}

		// Check left
		if (n.col > 0 && n.direction != 4) {
			if ((n.direction == 2 && n.moved < 3) || n.direction != 2) {
				if (n.direction == 2) {
					moved = n.moved + 1;
				} else {
					moved = 1;
				}
				if (!visited[n.row][n.col-1][2][moved] && n.distance + map[n.row][n.col-1] < distance[n.row][n.col-1][2][moved]) {
					distance[n.row][n.col-1][2][moved] = n.distance + map[n.row][n.col-1];
					struct node p;
					p.row = n.row;
					p.col = n.col-1;
					p.distance = n.distance + map[n.row][n.col-1];
					p.direction = 2;
					p.moved = moved;
					Q.push(p);
				}
			}
		}

		// Check down
		if (n.row < MAP_SIZE - 1 && n.direction != 1) {
			if ((n.direction == 3 && n.moved < 3) || n.direction != 3) {
				if (n.direction == 3) {
					moved = n.moved + 1;
				} else {
					moved = 1;
				}
				if (!visited[n.row+1][n.col][3][moved] &&n.distance + map[n.row+1][n.col] < distance[n.row+1][n.col][3][moved]) {
					distance[n.row+1][n.col][3][moved] = n.distance + map[n.row+1][n.col];
					struct node p;
					p.row = n.row+1;
					p.col = n.col;
					p.distance = n.distance + map[n.row+1][n.col];
					p.direction = 3;
					p.moved = moved;
					Q.push(p);
				}
			}
		}
		// Check right
		if (n.col < MAP_SIZE - 1 && n.direction != 2) {
			if ((n.direction == 4 && n.moved < 3) || n.direction != 4) {
				if (n.direction == 4) {
					moved = n.moved + 1;
				} else {
					moved = 1;
				}
				if (!visited[n.row][n.col+1][4][moved] && n.distance + map[n.row][n.col+1] < distance[n.row][n.col+1][4][moved]) {
					distance[n.row][n.col+1][4][moved] = n.distance + map[n.row][n.col+1];
					struct node p;
					p.row = n.row;
					p.col = n.col+1;
					p.distance = n.distance + map[n.row][n.col+1];
					p.direction = 4;
					p.moved = moved;
					Q.push(p);
				}
			}
		}
	}


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

	int32_t minimum = INT_MAX; 

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			minimum = min (minimum, distance[MAP_SIZE - 1][MAP_SIZE - 1][i][j]);
		}
	}

    cout << "Minimum heat loss at end " << minimum << " time taken " << duration.count() << " us" << endl;


}
