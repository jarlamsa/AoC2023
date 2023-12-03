#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct part_number {
    int number;
    int row;
    int startCol;
    int endCol;
    bool valid;
};

struct symbol {
    int row;
    int col;
};

int main()
{
	ifstream infile("input.txt");
	string buffer;

    vector<part_number *> parts;
    vector<symbol *> symbols;
    int row = 0;
    int partSum = 0;

	while(getline(infile, buffer)) {
        //Find first non .
        size_t pos = buffer.find_first_not_of('.');

        while (pos != string::npos) {
            //If we get a part number, check how long it is
            if (isdigit(buffer[pos])) {
                size_t endpos = buffer.find_first_not_of("0123456789", pos);
                struct part_number *foundPart = (struct part_number*) malloc(sizeof(struct part_number));
                if (endpos == string::npos) {
                    foundPart->number = stoi(buffer.substr(pos));
                    foundPart->endCol = buffer.size();
                } else {
                    foundPart->number = stoi(buffer.substr(pos, endpos - pos));
                    foundPart->endCol = endpos - 1;
                }
                foundPart->row = row;
                foundPart->startCol = pos;

                foundPart->valid = false;
                parts.push_back(foundPart);
                pos = endpos;
            } else {
                struct symbol *foundSymbol = (struct symbol*) malloc(sizeof(struct symbol));
                foundSymbol->row = row;
                foundSymbol->col = pos;
                symbols.push_back(foundSymbol);
                pos++;
            }

            pos = buffer.find_first_not_of('.', pos);
        }

        row++;
	}

    //Find if there is a validation symbol next to a part

    for (auto& part : parts) {
        for (auto& symb : symbols) {
            // Only check from current and the rows below and above
            if (part->row == symb->row - 1 || part->row == symb->row || part->row == symb->row +1 ) {
                //Adjacent row, check the column
                if (symb->col >= part->startCol - 1 && symb->col <= part->endCol + 1) {
                    part->valid = true;
                }
            }
        }
    }

    for(auto& part : parts) {
        if (part->valid) {
            partSum += part->number;
        }
    }

    cout << "Sum of valid part numbers: " << partSum << endl;

	return 0;
}
