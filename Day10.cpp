#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <sstream>
#include <limits>
#include <list>
#include "shared/Board.hpp"

int puzzle1();
int puzzle2();

int main(int argc, char* argv[]) {
	return puzzle1();
}

int puzzle1() {
	Board board("Inputs/Day10.txt", 55, 55);

	size_t total = 0;
	size_t uniqueTrails = 0;
	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.at(x, y) != '0') continue;
			std::set<Point> tops;
			//perform path finding with this as the initial point, breath first algorithm
			std::queue<Point> nodes;
			std::set<Point> visited;
			nodes.emplace(Point(x, y));
			while (!nodes.empty()) {
				const Point& node = nodes.front();
				//if (visited.count(node)) continue;
				//visited.insert(node);
				//check if it is a trail top
				if (board.at(node.x, node.y) == '9') {
					tops.emplace(node);
					uniqueTrails++;
				}
				else {
					if (node.x > 0 && board.at(node.x - 1, node.y) == board.at(node.x, node.y) + 1) nodes.emplace(Point(node.x - 1, node.y));
					if (node.x < board.getWidth() - 1 && board.at(node.x + 1, node.y) == board.at(node.x, node.y) + 1) nodes.emplace(Point(node.x + 1, node.y));
					if (node.y > 0 && board.at(node.x, node.y - 1) == board.at(node.x, node.y) + 1) nodes.emplace(Point(node.x, node.y - 1));
					if (node.y < board.getHeight() - 1 && board.at(node.x, node.y + 1) == board.at(node.x, node.y) + 1) nodes.emplace(Point(node.x, node.y + 1));
				}
				nodes.pop();
			}

			std::cout << tops.size() << '\n';
			total += tops.size();
		}
	}
	std::cout << total;
	std::cout << "Unique Trails: " << uniqueTrails << '\n';
	return 0;
}