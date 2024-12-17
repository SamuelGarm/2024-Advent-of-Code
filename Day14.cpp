#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <sstream>
#include <limits>
#include <set>
#include <math.h>
#include "Shared/Board.hpp"
#include "Shared/Point.hpp"

int puzzle1();
int puzzle2();

int main(int argc, char* argv[]) {
	return puzzle2();
}

struct Bot {
	long long int px;
	long long int py;
	long long int vx;
	long long int vy;
};

int puzzle1() {
	std::ifstream inFile("Inputs/Day14.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	std::vector<Bot> bots;
	std::string inLine;
	while (std::getline(inFile, inLine)) {
		Bot bot;
		std::string pos = inLine.substr(2, inLine.find(' ')-2);
		std::string vel = inLine.substr(inLine.find(' ')+3);

		bot.px = std::stoll(pos.substr(0, pos.find(',')));
		bot.py = std::stoll(pos.substr(pos.find(',')+1));
		
		bot.vx = std::stoll(vel.substr(0, vel.find(',')));
		bot.vy = std::stoll(vel.substr(vel.find(',') + 1));

		bots.push_back(bot);
	}


	//update all the bots by n steps
	unsigned int numSteps = 1;
	const int width = 101;
	const int height = 103;

	size_t currStep = 0;
	do {
		currStep++;
		std::cout << "starting step " << currStep << '\n';
		for (auto& bot : bots) {
			//std::cout << "(px,py): " << bot.px << ' ' << bot.py << " -> ";	
			bot.px += bot.vx * numSteps;
			bot.py += bot.vy * numSteps;

			//p=0,4 v=3,-3
			//0,4
			//3,1
			//1,3
			//4,0
			//2,2

			//wrap the bot around the boundaries
			if (bot.px >= 0) {
				bot.px = bot.px % width;
			}
			else {
				bot.px = ((width - 1) - ((-bot.px - 1) % width)) % width;
			}

			if (bot.py >= 0) {
				bot.py = bot.py % height;
			}
			else {
				bot.py = ((height - 1) - ((-bot.py - 1) % height)) % height;
			}
			//std::cout << "(px,py): " << bot.px << ' ' << bot.py << '\n';
		}

		//Debug visualization
		Board board('.', width, height);
		if (!board.isValid)
			return 1;

		for (auto& bot : bots)
			board.set(bot.px, bot.py, 'X');
		board.printBoard();
		std::cout << '\n';
	} while (std::cin.get() == '\n');
	
	//calculate robots in each quad
	unsigned int quadWidth = width / 2;
	unsigned int quadHeight = height / 2;
	size_t safetyFactor = 0;

	unsigned int tr_count = 0; //tr
	unsigned int tl_count = 0; //tl
	unsigned int bl_count = 0; //bl
	unsigned int br_count = 0; //br

	for (const Bot& bot : bots) {
		if (bot.px < quadWidth) {
			if (bot.py < quadHeight)
				tl_count++;
			else if (bot.py != quadHeight)
				bl_count++;
		}
		else if (bot.px != quadWidth)
			if (bot.py < quadHeight)
				tr_count++;
			else if (bot.py != quadHeight)
				br_count++;
	}

	safetyFactor = tl_count * tr_count * br_count * bl_count;

	std::cout << "TL: " << tl_count << "\nTR: " << tr_count << "\nBL: " << bl_count << "\nBR: " << br_count << '\n';
	std::cout << safetyFactor << '\n';

	return 1;
}



int puzzle2() {
	std::ifstream inFile("Inputs/Day14.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	std::vector<Bot> bots;
	std::string inLine;
	while (std::getline(inFile, inLine)) {
		Bot bot;
		std::string pos = inLine.substr(2, inLine.find(' ') - 2);
		std::string vel = inLine.substr(inLine.find(' ') + 3);

		bot.px = std::stoll(pos.substr(0, pos.find(',')));
		bot.py = std::stoll(pos.substr(pos.find(',') + 1));

		bot.vx = std::stoll(vel.substr(0, vel.find(',')));
		bot.vy = std::stoll(vel.substr(vel.find(',') + 1));

		bots.push_back(bot);
	}


	//update all the bots by n steps
	unsigned int numSteps = 1;
	const int width = 101;
	const int height = 103;

	size_t currStep = 0;
	do {
		currStep++;
		std::cout << "starting step " << currStep;
		for (auto& bot : bots) {
			//std::cout << "(px,py): " << bot.px << ' ' << bot.py << " -> ";	
			bot.px += bot.vx * numSteps;
			bot.py += bot.vy * numSteps;

			//p=0,4 v=3,-3
			//0,4
			//3,1
			//1,3
			//4,0
			//2,2

			//wrap the bot around the boundaries
			if (bot.px >= 0) {
				bot.px = bot.px % width;
			}
			else {
				bot.px = ((width - 1) - ((-bot.px - 1) % width)) % width;
			}

			if (bot.py >= 0) {
				bot.py = bot.py % height;
			}
			else {
				bot.py = ((height - 1) - ((-bot.py - 1) % height)) % height;
			}
			//std::cout << "(px,py): " << bot.px << ' ' << bot.py << '\n';
		}

		//Debug visualization
		Board board(' ', width, height);
		Board groupSearchBoard('0', width, height);
		if (!board.isValid)
			return 1;

		for (auto& bot : bots) {
			board.set(bot.px, bot.py, 'X');
			groupSearchBoard.set(bot.px, bot.py, 'X');
		}

		//calculate the size of the largest group of bots
		size_t largestGroup = 0;
		for (int y = 0; y < groupSearchBoard.getHeight(); y++) {
			for (int x = 0; x < groupSearchBoard.getWidth(); x++) {
				if (groupSearchBoard.at(x, y) == '0') continue;
				size_t groupSize = 0;
				std::set<Point> toSearch;
				toSearch.insert(Point(x, y));
				while (!toSearch.empty()) {
					char unsearchedNeighbourCount = '0';
					auto it = toSearch.begin();
					const Point loc = *it;
					toSearch.erase(it);
					const char currChar = groupSearchBoard.at(loc.x, loc.y);

					//x+1
					Point neighbour = loc;
					if (loc.x < groupSearchBoard.getWidth() - 1) {
						neighbour.x += 1;
						if (groupSearchBoard.at(neighbour.x, neighbour.y) == currChar) {
							toSearch.insert(Point(neighbour.x, neighbour.y));
							unsearchedNeighbourCount++;
							groupSize++;
						}
						else if (groupSearchBoard.at(neighbour.x, neighbour.y) >= '1' && groupSearchBoard.at(neighbour.x, neighbour.y) <= '4') {
							groupSearchBoard.set(neighbour.x, neighbour.y, groupSearchBoard.at(neighbour.x, neighbour.y) - 1);
						}
					}

					//x-1
					if (loc.x > 0) {
						neighbour = loc;
						neighbour.x -= 1;
						if (groupSearchBoard.at(neighbour.x, neighbour.y) == currChar) {
							toSearch.insert(Point(neighbour.x, neighbour.y));
							unsearchedNeighbourCount++;
							groupSize++;
						}
						else if (groupSearchBoard.at(neighbour.x, neighbour.y) >= '1' && groupSearchBoard.at(neighbour.x, neighbour.y) <= '4') {
							groupSearchBoard.set(neighbour.x, neighbour.y, groupSearchBoard.at(neighbour.x, neighbour.y) - 1);
						}
					}

					//y+1
					if (loc.y < groupSearchBoard.getHeight() - 1) {
						neighbour = loc;
						neighbour.y += 1;
						if (groupSearchBoard.at(neighbour.x, neighbour.y) == currChar) {
							toSearch.insert(Point(neighbour.x, neighbour.y));
							unsearchedNeighbourCount++;
							groupSize++;
						}
						else if (groupSearchBoard.at(neighbour.x, neighbour.y) >= '1' && groupSearchBoard.at(neighbour.x, neighbour.y) <= '4') {
							groupSearchBoard.set(neighbour.x, neighbour.y, groupSearchBoard.at(neighbour.x, neighbour.y) - 1);
						}
					}

					//y-1
					if (loc.y > 0) {
						neighbour = loc;
						neighbour.y -= 1;
						if (groupSearchBoard.at(neighbour.x, neighbour.y) == currChar) {
							toSearch.insert(Point(neighbour.x, neighbour.y));
							unsearchedNeighbourCount++;
							groupSize++;
						}
						else if (groupSearchBoard.at(neighbour.x, neighbour.y) >= '1' && groupSearchBoard.at(neighbour.x, neighbour.y) <= '4') {
							groupSearchBoard.set(neighbour.x, neighbour.y, groupSearchBoard.at(neighbour.x, neighbour.y) - 1);
						}
					}

					groupSearchBoard.set(loc.x, loc.y, unsearchedNeighbourCount);
				}
				if (groupSize > largestGroup)
					largestGroup = groupSize;
			}
		}

		std::cout << "  Largest group: " << largestGroup << '\n';

		if (largestGroup >= 10) {
			board.printBoard();
			std::cout << '\n';

			std::cin.get();
		}
			

	} while (true);

	return 1;
}