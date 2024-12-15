#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <stack>
#include <sstream>
#include <limits>
#include "Shared/Board.hpp"
#include "Shared/Point.hpp"
#include <set>

int puzzle1();
int puzzle2();

int main(int argc, char* argv[]) {
	return puzzle2();
}

int puzzle1() {
	Board board("Inputs/Day12.txt", 140, 140);
	
	size_t totalCost = 0;

	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.at(x, y) == '0') continue;
			size_t perimeter = 0;
			size_t area = 0;
			std::set<Point> toSearch;
			toSearch.insert(Point(x, y));
			//std::cout << "Starting plot search\n";
			//board.printBoard();
			//std::cout << '\n';
			while (!toSearch.empty()) {
				char unsearchedNeighbourCount = '0';
				auto it = toSearch.begin();
				const Point loc = *it;
				toSearch.erase(it);
				const char currChar = board.at(loc.x, loc.y);

				//check for side count by looking for unique corners
				if (board.at(loc.x + 1, loc.y));

				//x+1
				Point neighbour = loc;
				if (loc.x < board.getWidth() - 1) {
					neighbour.x += 1;
					if (board.at(neighbour.x, neighbour.y) == currChar) {
						toSearch.insert(Point(neighbour.x, neighbour.y));
						unsearchedNeighbourCount++;
					}
					else if (board.at(neighbour.x, neighbour.y) >= '1' && board.at(neighbour.x, neighbour.y) <= '4') {
						board.set(neighbour.x, neighbour.y, board.at(neighbour.x, neighbour.y) - 1);
					}
					else {
						perimeter++;
					}
				}
				else {
					perimeter++;
				}
				
				
				//x-1
				if (loc.x > 0) {
					neighbour = loc;
					neighbour.x -= 1;
					if (board.at(neighbour.x, neighbour.y) == currChar) {
						toSearch.insert(Point(neighbour.x, neighbour.y));
						unsearchedNeighbourCount++;
					}
					else if (board.at(neighbour.x, neighbour.y) >= '1' && board.at(neighbour.x, neighbour.y) <= '4') {
						board.set(neighbour.x, neighbour.y, board.at(neighbour.x, neighbour.y) - 1);
					}
					else {
						perimeter++;
					}
				}
				else {
					perimeter++;
				}

				//y+1
				if (loc.y < board.getHeight() - 1) {
					neighbour = loc;
					neighbour.y += 1;
					if (board.at(neighbour.x, neighbour.y) == currChar) {
						toSearch.insert(Point(neighbour.x, neighbour.y));
						unsearchedNeighbourCount++;
					}
					else if (board.at(neighbour.x, neighbour.y) >= '1' && board.at(neighbour.x, neighbour.y) <= '4') {
						board.set(neighbour.x, neighbour.y, board.at(neighbour.x, neighbour.y) - 1);
					}
					else {
						perimeter++;
					}
				}
				else {
					perimeter++;
				}

				//y-1
				if (loc.y > 0) {
					neighbour = loc;
					neighbour.y -= 1;
					if (board.at(neighbour.x, neighbour.y) == currChar) {
						toSearch.insert(Point(neighbour.x, neighbour.y));
						unsearchedNeighbourCount++;
					}
					else if (board.at(neighbour.x, neighbour.y) >= '1' && board.at(neighbour.x, neighbour.y) <= '4') {
						board.set(neighbour.x, neighbour.y, board.at(neighbour.x, neighbour.y) - 1);
					}
					else {
						perimeter++;
					}
				}
				else {
					perimeter++;
				}

				board.set(loc.x, loc.y, unsearchedNeighbourCount);
				area++;
				//board.printBoard();
				//std::cout << '\n';
			}
			totalCost += area * perimeter;
			//std::cout << "Area: " << area << " Perimiter: " << perimeter << '\n';
		}
	}

	std::cout << "Cost total: " << totalCost << '\n';

	return 0;
}

enum Direction {
	UP, DOWN, LEFT, RIGHT
};

struct Edge {
	Edge(size_t _p, Direction _dir) : p(_p), dir(_dir) {};
	size_t p;
	Direction dir;
};

int puzzle2() {
	Board board("Inputs/Day12.txt", 140, 140);

	size_t totalCost = 0;

	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.at(x, y) == '-') continue;
			size_t perimeter = 0;
			size_t area = 0;
			std::set<Point> toSearch;
			std::set<Point> region;
			size_t min_x = 0, max_x = 0, min_y = 0, max_y = 0;
			toSearch.insert(Point(x, y));
			//std::cout << "Starting plot search\n";
			//board.printBoard();
			//std::cout << '\n';
			while (!toSearch.empty()) {
				auto it = toSearch.begin();
				const Point loc = *it;
				region.insert(*it);
				toSearch.erase(it);
				const char currChar = board.at(loc.x, loc.y);

				//update bounding box
				if (loc.x < min_x) min_x = loc.x;
				if (loc.x > max_x) max_x = loc.x;
				if (loc.y < min_y) min_y = loc.y;
				if (loc.y > max_y) max_y = loc.y;

				//x+1
				Point neighbour = loc;
				if (loc.x < board.getWidth() - 1) {
					neighbour.x += 1;
					if (board.at(neighbour.x, neighbour.y) == currChar) {
						toSearch.insert(Point(neighbour.x, neighbour.y));
					}
				}


				//x-1
				if (loc.x > 0) {
					neighbour = loc;
					neighbour.x -= 1;
					if (board.at(neighbour.x, neighbour.y) == currChar) {
						toSearch.insert(Point(neighbour.x, neighbour.y));
					}
				}

				//y+1
				if (loc.y < board.getHeight() - 1) {
					neighbour = loc;
					neighbour.y += 1;
					if (board.at(neighbour.x, neighbour.y) == currChar) {
						toSearch.insert(Point(neighbour.x, neighbour.y));
					}
				}

				//y-1
				if (loc.y > 0) {
					neighbour = loc;
					neighbour.y -= 1;
					if (board.at(neighbour.x, neighbour.y) == currChar) {
						toSearch.insert(Point(neighbour.x, neighbour.y));
					}
				}

				
				board.set(loc.x, loc.y, '-');
				area++;
				//board.printBoard();
				//std::cout << '\n';
			}

			//calculate the side count
			//find top sides


			totalCost += area * perimeter;
			//std::cout << "Area: " << area << " Perimiter: " << perimeter << '\n';
		}
	}

	std::cout << "Cost total: " << totalCost << '\n';

	return 0;
}