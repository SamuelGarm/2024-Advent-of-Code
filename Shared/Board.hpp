#include <fstream>

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
		inFile.close();
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