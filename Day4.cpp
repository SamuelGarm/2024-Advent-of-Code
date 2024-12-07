#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>

int puzzle1();
int puzzle2();

//this class represents a board of single characters. It is assumed that the board is not jagged
class Board {
public:
	bool isValid = false;
	Board(const std::string& file, size_t width, size_t height) : width(width), height(height)
	{
		std::ifstream inFile(file);
		if (!inFile.is_open()) {
			std::cerr << "Error opening the file!";
			return;
		}
		data = (char*)malloc(width * height * sizeof(char));
		if (!data)
			return;
		//populate the array in row major order
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				char c = (char)inFile.get();
				if(c == '\n')
					c = (char)inFile.get();
				data[(y * width * sizeof(char)) + (x * sizeof(char))] = c;
			}
		}
		isValid = true;
	}
	char at(const int x, const int y) { return data[(y * width * sizeof(char)) + (x * sizeof(char))]; };
	~Board() {
		free(data);
	}
private:
	size_t width, height;
	char* data = nullptr;
};

int main(int argc, char* argv[]) {

	return puzzle2();
}

int puzzle1() {
	const int boardWidth = 140;
	const int boardHeight = 140;
	Board board("Inputs/Day4.txt", boardWidth, boardHeight);
	if (!board.isValid)
		return 1;
	//print out board
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			std::cout << board.at(x, y);
		}
		std::cout << '\n';
	}
	
	int count = 0;
	//search for an X
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			if (board.at(x, y) == 'X') {
				//search in all directions for the full XMAS
				for (int x_off = -1; x_off < 2; x_off++) {
					for (int y_off = -1; y_off < 2; y_off++) {
						int currX = x, currY = y;
						bool sucess = true;
						for each(char c in "MAS") {
							if (c == '\0') break;
							//move to the next spot in the board
							currX += x_off;
							currY += y_off;
							//make sure it is in bounds
							if (currX < 0 || currY < 0 || currX >= boardWidth || currY >= boardHeight) {
								sucess = false; break;
							}
							//check if the spot has the next letter
							if (board.at(currX, currY) != c) {
								sucess = false; break;
							}
						}
						count += sucess;
					}
				}
			}
		}
	}
	std::cout << count << '\n';
	return 0;
}


int puzzle2() {
	const int boardWidth = 140;
	const int boardHeight = 140;
	Board board("Inputs/Day4.txt", boardWidth, boardHeight);
	if (!board.isValid)
		return 1;
	//print out board
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			std::cout << board.at(x, y);
		}
		std::cout << '\n';
	}

	int count = 0;
	//search for an X
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			if (board.at(x, y) == 'A') {
				//check in an x pattern
				if (y == 0 || x == 0 || y == boardHeight - 1 || x == boardWidth - 1) continue;
				int found = 0;
				if (board.at(x - 1, y - 1) == 'M' && board.at(x + 1, y + 1) == 'S') found++;
				if (board.at(x - 1, y - 1) == 'S' && board.at(x + 1, y + 1) == 'M') found++;
				if (board.at(x - 1, y + 1) == 'M' && board.at(x + 1, y - 1) == 'S') found++;
				if (board.at(x - 1, y + 1) == 'S' && board.at(x + 1, y - 1) == 'M') found++;
				if (found == 2)
					count++;
			}
		}
	}
	std::cout << count << '\n';
	return 0;
}
