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
			std::cout << "Plot: " << board.at(x, y) << '\n';
			size_t perimeter = 0;
			size_t area = 0;
			std::set<Point> toSearch;
			std::set<Point> region;
			size_t min_x = INT64_MAX, max_x = 0, min_y = INT64_MAX, max_y = 0;
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
			size_t sides = 0;
			//find top sides by iterating over the isolated region set and the derived bounding box
			for (int y = min_y; y <= max_y; y++) {
				bool edgeStarted = false;
				for (int x = min_x; x <= max_x; x++) {
					//if we are tracing an edge check for it stopping
					if (edgeStarted) {
						//the 2 ways an edge can stop is 1. the line stops 2. there is something above it
						if (!region.count(Point(x, y)) || region.count(Point(x, y - 1))) {
							edgeStarted = false;
							sides++;
						}
					}
					//if we are not tracing an edge we need to check if we can start tracing a new edge
					//a new edge starts if we are on a point with no point above it (so the edge exists)
					else {
						if (region.count(Point(x, y)) && !region.count(Point(x, y-1))) {
							edgeStarted = true;
						}
					}
				}
				//if are tracing an edge and reach the border then we know that edge terminates and is a side
				if (edgeStarted)
					sides++;
			}

			//std::cout << "\tTop Sides: " << sides << '\n';
			//sides = 0;

			//bottom sides
			for (int y = min_y; y <= max_y; y++) {
				bool edgeStarted = false;
				for (int x = min_x; x <= max_x; x++) {
					//if we are tracing an edge check for it stopping
					if (edgeStarted) {
						//the 2 ways an edge can stop is 1. the line stops 2. there is something below it
						if (!region.count(Point(x, y)) || region.count(Point(x, y + 1))) {
							edgeStarted = false;
							sides++;
						}
					}
					//if we are not tracing an edge we need to check if we can start tracing a new edge
					//a new edge starts if we are on a point with no point above it (so the edge exists)
					else {
						if (region.count(Point(x, y)) && !region.count(Point(x, y + 1))) {
							edgeStarted = true;
						}
					}
				}
				//if are tracing an edge and reach the border then we know that edge terminates and is a side
				if (edgeStarted)
					sides++;
			}

			//std::cout << "\tBottom Sides: " << sides << '\n';
			//sides = 0;

			//left sides
			for (int x = min_x; x <= max_x; x++) {
				bool edgeStarted = false;
				for (int y = min_y; y <= max_y; y++) {
					//if we are tracing an edge check for it stopping
					if (edgeStarted) {
						//the 2 ways an edge can stop is 1. the line stops 2. there is something below it
						if (!region.count(Point(x, y)) || region.count(Point(x - 1, y))) {
							edgeStarted = false;
							sides++;
						}
					}
					//if we are not tracing an edge we need to check if we can start tracing a new edge
					//a new edge starts if we are on a point with no point above it (so the edge exists)
					else {
						if (region.count(Point(x, y)) && !region.count(Point(x - 1, y))) {
							edgeStarted = true;
						}
					}
				}
				//if are tracing an edge and reach the border then we know that edge terminates and is a side
				if (edgeStarted)
					sides++;
			}

			//std::cout << "\tLeft Sides: " << sides << '\n';
			//sides = 0;

			//left sides
			for (int x = min_x; x <= max_x; x++) {
				bool edgeStarted = false;
				for (int y = min_y; y <= max_y; y++) {
					//if we are tracing an edge check for it stopping
					if (edgeStarted) {
						//the 2 ways an edge can stop is 1. the line stops 2. there is something below it
						if (!region.count(Point(x, y)) || region.count(Point(x + 1, y))) {
							edgeStarted = false;
							sides++;
						}
					}
					//if we are not tracing an edge we need to check if we can start tracing a new edge
					//a new edge starts if we are on a point with no point above it (so the edge exists)
					else {
						if (region.count(Point(x, y)) && !region.count(Point(x + 1, y))) {
							edgeStarted = true;
						}
					}
				}
				//if are tracing an edge and reach the border then we know that edge terminates and is a side
				if (edgeStarted)
					sides++;
			}

			//std::cout << "\tRight Sides: " << sides << '\n';
			//sides = 0;

			std::cout << "Region Cost: " << area * sides << '\n';
			totalCost += area * sides;
			//std::cout << "Area: " << area << " Perimiter: " << perimeter << '\n';
		}
	}

	std::cout << "Cost total: " << totalCost << '\n';

	return 0;
}