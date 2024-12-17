#pragma once
#include <fstream>
#include <cassert>

//this class represents a board of single characters. It is assumed that the board is not jagged
class Board {
public:
	bool isValid = false;

	Board() = delete;
	Board& operator=(const Board&) = delete;

	inline char at(const int x, const int y) const {
		assert(x >= 0 && x < width);
		assert(y >= 0 && y < height);
		return data[(y * width * sizeof(char)) + (x * sizeof(char))]; 
	};
	inline void set(const int x, const int y, const char c) { 
		assert(x >= 0 && x < width);
		assert(y >= 0 && y < height);
		data[(y * width * sizeof(char)) + (x * sizeof(char))] = c; 
	};

	//populate a board from a file
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
				//data[(y * width * sizeof(char)) + (x * sizeof(char))] = c;
				set(x, y, c);
			}
		}
		isValid = true;
		inFile.close();
	}

	//fill a board with a single characer
	Board(const char c, size_t width, size_t height) : width(width), height(height) {
		data = (char*)malloc(width * height * sizeof(char));
		if (!data)
			return;
		//populate the array in row major order
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				//data[(y * width * sizeof(char)) + (x * sizeof(char))] = c;
				set(x, y, c);
			}
		}
		isValid = true;
	}

	//copy constructor
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
		isValid = false;
		if (data) {
			free(data);
			data = nullptr;
		}
	}
	int getWidth() const { return width; };
	int getHeight() const { return height; };
private:
	size_t width, height;
	char* data = nullptr;
};