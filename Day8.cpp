#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>

int puzzle1();
int puzzle2();

int main(int argc, char* argv[]) {
	return puzzle2();
}

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {};
	bool operator==(const Point& other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator<(const Point& other) const {
		if (x == other.x) return y < other.y;
		else return x < other.x;
	}

	Point operator+(const Point& other) const {
		return Point(x + other.x, y + other.y);
	}

	Point operator-(const Point& other) const {
		return Point(x - other.x, y - other.y);
	}

	Point operator*(const int other) const {
		return Point(x * other, y * other);
	}
};

int puzzle1() {
	std::ifstream inFile("Inputs/Day8.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	std::map<char, std::vector<Point>> points; //each vector contains all the points for signals of a certain frequency 
	std::string inLine;
	int x = 0, y = 0;
	while (std::getline(inFile, inLine)) {
		x = 0;
		std::istringstream ss(inLine);
		char c;
		while (ss.get(c)) {
			if (c != '.') 
				points[c].push_back(Point(x, y));
			x++;
		}
		y++;
	}
	inFile.close();

	for (const auto& [key, value] : points) {
		std::cout << key << '\n';
		for (auto p : value) {
			std::cout << "\t(" << p.x << ',' << p.y << ")\n";
		}
	}

	//loop over each vector in the map for each type and calculate all antinodes
	std::set<Point> antinodePoints;
	for (const auto& [key, value] : points) {
		if (value.size() < 2) continue;
		for (int p1 = 0; p1 < value.size() - 1; p1++) {
			for (int p2 = p1 + 1; p2 < value.size(); p2++) {
				Point antinode1 = (value[p1] * 2) - value[p2];
				Point antinode2 = (value[p2] * 2) - value[p1];
				if(antinode1.x >= 0 && antinode1.x < 50 && antinode1.y >= 0 && antinode1.y < 50)
					antinodePoints.insert(antinode1);
				if (antinode2.x >= 0 && antinode2.x < 50 && antinode2.y >= 0 && antinode2.y < 50)
					antinodePoints.insert(antinode2);
			}
		}
	}

	std::cout << antinodePoints.size() << '\n';

	return 0;
}


int puzzle2() {
	std::ifstream inFile("Inputs/Day8.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	std::map<char, std::vector<Point>> points; //each vector contains all the points for signals of a certain frequency 
	std::string inLine;
	int x = 0, y = 0;
	while (std::getline(inFile, inLine)) {
		x = 0;
		std::istringstream ss(inLine);
		char c;
		while (ss.get(c)) {
			if (c != '.')
				points[c].push_back(Point(x, y));
			x++;
		}
		y++;
	}
	inFile.close();

	for (const auto& [key, value] : points) {
		std::cout << key << '\n';
		for (auto p : value) {
			std::cout << "\t(" << p.x << ',' << p.y << ")\n";
		}
	}

	//loop over each vector in the map for each type and calculate all antinodes for any pair of points
	std::set<Point> antinodePoints;
	for (const auto& [key, value] : points) {
		if (value.size() < 2) continue;
		for (int p1 = 0; p1 < value.size() - 1; p1++) {
			for (int p2 = p1 + 1; p2 < value.size(); p2++) {
				Point dir = value[p1] - value[p2];
				//shorten the dir vector to the smallest possible while remaining an integer
				int gcd = std::gcd(dir.x, dir.y);
				dir.x /= gcd;
				dir.y /= gcd; //50
				//explore in one direction
				for (int m = 0; true; m++) {
					Point antinode = value[p1] + (dir * m);
					if (antinode.x >= 0 && antinode.x < 50 && antinode.y >= 0 && antinode.y < 50)
						antinodePoints.insert(antinode);
					else
						break;
				}

				//explore the direction
				for (int m = 0; true; m--) {
					Point antinode = value[p2] + (dir * m);
					if (antinode.x >= 0 && antinode.x < 50 && antinode.y >= 0 && antinode.y < 50)
						antinodePoints.insert(antinode);
					else
						break;
				}
			}
		}
	}

	std::cout << antinodePoints.size() << '\n';

	return 0;
}