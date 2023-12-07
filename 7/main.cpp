#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct card_hand {
    uint32_t type = 0;
    uint32_t bid;
    string hand;
    int handNum[5] = {0};
};

bool compareHands(const struct card_hand &a, const struct card_hand &b)
{
    if (a.type == b.type) {
        for (int i = 0; i < 5; i++) {
            if (a.handNum[i] != b.handNum[i]) {
                return a.handNum[i] < b.handNum[i];
            }
        }
    }

    return a.type < b.type;
}

uint32_t countType(struct card_hand &hand)
{
    uint32_t type = 0;
    uint32_t cards[13] = {0};

    for (int i = 0; i < 5; i++) {
        uint64_t power;
        if (hand.hand[i] == 'A') {
            power = 14;
        } else if (hand.hand[i] == 'K') {
            power = 13;
        } else if (hand.hand[i] == 'Q') {
            power = 12;
        } else if (hand.hand[i] == 'J') {
            power = 11;
        } else if (hand.hand[i] == 'T') {
            power = 10;
        } else {
            power = hand.hand[i] - '0';
        }

        power -= 2;
        cards[power]++;
        hand.handNum[i] = power;
    }

    for (int i = 0; i < 13; i++) {
        if (cards[i] == 5) {
            type = 6;
            break;
        } else if (cards[i] == 4) {
            type = 5;
            break;
        } else if (cards[i] == 3) {
            if (type == 1) {
                type = 4;
                break;
            } else {
                type = 3;
            }
        } else if (cards[i] == 2) {
            if (type == 1) {
                type = 2;
            } else if (type == 3) {
                type = 4;
                break;
            } else {
                type = 1;
            }
        }
    }

    return type;
}

int main()
{
	ifstream infile("input.txt");
	string buffer;
    vector<card_hand> hands;

	while(getline(infile, buffer)) {
        stringstream ss(buffer);
        struct card_hand hand;
        ss >> hand.hand;
        ss >> hand.bid;

        hand.type = countType(hand);
        hands.push_back(hand);
	}

    std::sort(hands.begin(), hands.end(), compareHands);

    uint64_t rank = 1;
    uint64_t totalWinning = 0;
    for (auto hand : hands) {
        totalWinning += hand.bid * rank;
        rank++;
    }

    cout << "Total winnings " << totalWinning << endl;

	return 0;
}
