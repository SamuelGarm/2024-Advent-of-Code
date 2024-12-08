#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
				if (c == '\n')
					c = (char)inFile.get();
				data[(y * width * sizeof(char)) + (x * sizeof(char))] = c;
			}
		}
		isValid = true;
	}
	Board(const Board& board) {
		width = board.width;
		height = board.height;
		data = (char*)malloc(width * height * sizeof(char));
		//copy data
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				set(x, y, board.at(x, y));
			}
		}
	}

	char at(const int x, const int y) const { return data[(y * width * sizeof(char)) + (x * sizeof(char))]; };
	void set(const int x, const int y, const char c) { data[(y * width * sizeof(char)) + (x * sizeof(char))] = c; };
	void printBoard() {
		//print out board
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				std::cout << at(x, y);
			}
			std::cout << '\n';
		}
	}
	~Board() {
		free(data);
	}
	int getWidth() const { return width; };
	int getHeight() const { return height; };
private:
	size_t width, height;
	char* data = nullptr;
};

int main(int argc, char* argv[]) {

	return puzzle2();
}

//returns true if the guard leaves the board, false if the guard is stuck in a loop
bool walkGuard(const Board& _board) {
	Board board(_board); //create a copy of the board to work on
	//load the board
	const int boardWidth = board.getWidth();
	const int boardHeight = board.getHeight();

	enum Direction
	{
		UP, RIGHT, DOWN, LEFT
	};
	int guard_x = -1, guard_y = -1;
	Direction guard_d = LEFT;
	//locate the guard
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			const char c = board.at(x, y);
			if (c == '^' || c == '>' || c == '<' || c == 'v') {
				guard_x = x;
				guard_y = y;
				if (c == '^') guard_d = Direction::UP;
				if (c == 'v') guard_d = Direction::DOWN;
				if (c == '<') guard_d = Direction::LEFT;
				if (c == '>') guard_d = Direction::RIGHT;
			}
		}
	}

	int iterations = 0;
	//walk the guard and write # to the guards position BEFORE each movement
	while (guard_x >= 0 && guard_x < boardWidth && guard_y >= 0 && guard_y < boardHeight) {
		iterations++;
		//check the guards direction 
		switch (guard_d) {
		case Direction::UP:
			board.set(guard_x, guard_y, '^');
			if (guard_y > 0 && board.at(guard_x, guard_y - 1) == '#')
				guard_d = Direction::RIGHT;
			else
				guard_y -= 1;
			break;

		case Direction::DOWN:
			board.set(guard_x, guard_y, 'v');
			if (guard_y < boardHeight - 1 && board.at(guard_x, guard_y + 1) == '#')
				guard_d = Direction::LEFT;
			else
				guard_y += 1;
			break;

		case Direction::LEFT:
			board.set(guard_x, guard_y, '<');
			if (guard_x > 0 && board.at(guard_x - 1, guard_y) == '#')
				guard_d = Direction::UP;
			else
				guard_x -= 1;
			break;

		case Direction::RIGHT:
			board.set(guard_x, guard_y, '>');
			if (guard_x < boardWidth - 1 && board.at(guard_x + 1, guard_y) == '#')
				guard_d = Direction::DOWN;
			else
				guard_x += 1;
			break;
		}

		if (false)
			board.printBoard();

		//check if the guard is in their starting position, indicating a loop
		if ((guard_d == UP && board.at(guard_x, guard_y) == '^') ||
			(guard_d == DOWN && board.at(guard_x, guard_y) == 'v') ||
			(guard_d == LEFT && board.at(guard_x, guard_y) == '<') ||
			(guard_d == RIGHT && board.at(guard_x, guard_y) == '>') ||
			iterations > (board.getWidth() * board.getHeight() * 2)) //assume that if we do this many iterations the guard is in a loop...
			return false;
	}
	return true;
}

//for puzzle 2 we need to rephrase this as a graph problem
//1. build a network 
int puzzle2() {
	//load the board
	const int boardWidth = 130;
	const int boardHeight = 130;
	Board board("Inputs/Day6.txt", boardWidth, boardHeight);
	if (!board.isValid)
		return 1;

	int count = 0;
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			std::cout << (y * boardWidth) + x << '/' << boardHeight * boardWidth << '\n';
			const char c = board.at(x, y);
			//make sure the location is empty
			if (c != '.') continue;
			board.set(x, y, '#');
			bool result = walkGuard(board);
			board.set(x, y, '.');
			if (!result) count++;
		}
	}
	std::cout << count << '\n';
}

int puzzle1() {
	//load the board
	const int boardWidth = 130;
	const int boardHeight = 130;
	Board board("Inputs/Day6.txt", boardWidth, boardHeight);
	if (!board.isValid)
		return 1;
	//board.printBoard();

	enum Direction
	{
		UP, RIGHT, DOWN, LEFT
	};
	int guard_x, guard_y;
	Direction guard_d;
	//locate the guard
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			const char c = board.at(x, y);
			if (c == '^' || c == '>' || c == '<' || c == 'v') {
				guard_x = x;
				guard_y = y;
				if (c == '^') guard_d = Direction::UP;
				if (c == 'v') guard_d = Direction::DOWN;
				if (c == '<') guard_d = Direction::LEFT;
				if (c == '>') guard_d = Direction::RIGHT;
			}
		}
	}

	//walk the guard and write # to the guards position BEFORE each movement
	while (guard_x >= 0 && guard_x < boardWidth && guard_y >= 0 && guard_y < boardHeight) {
		board.set(guard_x, guard_y, 'X');
		//check the guards direction 
		switch (guard_d) {
		case Direction::UP:
			if (guard_y > 0 && board.at(guard_x, guard_y - 1) == '#')
				guard_d = Direction::RIGHT;
			else
				guard_y -= 1;
			break;

		case Direction::DOWN:
			if (guard_y < boardHeight - 1 && board.at(guard_x, guard_y + 1) == '#')
				guard_d = Direction::LEFT;
			else
				guard_y += 1;
			break;

		case Direction::LEFT:
			if (guard_x > 0 && board.at(guard_x - 1, guard_y) == '#')
				guard_d = Direction::UP;
			else
				guard_x -= 1;
			break;

		case Direction::RIGHT:
			if (guard_x < boardWidth - 1 && board.at(guard_x + 1, guard_y) == '#')
				guard_d = Direction::DOWN;
			else
				guard_x += 1;
			break;
		}
		//std::cout << '\n';
		//board.printBoard();
	}

	int count = 0;
	//count how many X are on the board
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			if (board.at(x, y) == 'X') count++;
		}
	}
	std::cout << count << '\n';
}