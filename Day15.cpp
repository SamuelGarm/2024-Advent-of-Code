#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <queue>
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

int puzzle1() {
	Board board("Inputs/Day15.txt", 50, 50);
	Point robotPos({ 0,0 });

	//find the robots position
	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.at(x, y) == '@') {
				robotPos.x = x;
				robotPos.y = y;

				//break the loop
				y = board.getHeight();
				break;
			}
		}
	}

	//parse the sequence
	std::ifstream inFile("Inputs/Day15.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	std::string inLine;
	bool readingCommands = false;
	std::vector<char> commands;
	while (std::getline(inFile, inLine)) {
		if (readingCommands) {
			for (char c : inLine) {
				if (c != '\n')
					commands.push_back(c);
			}
		}
		else if (inLine.length() == 0) 
			readingCommands = true;
	}
	inFile.close();

	//preform commands
	for (char c : commands) {
		Point dir(0,0);
		if (c == '<')
			dir.x = -1;
		else if (c == '>')
			dir.x = 1;
		else if (c == 'v')
			dir.y = 1;
		else if (c == '^')
			dir.y = -1;

		//std::cout << "Command: " << c << '\n';
		
		//move the robot and boxes
		Point newPos = robotPos + dir;
		//check if the robot would intersect a wall
		if (board.at(newPos.x, newPos.y) == '#') 
			continue;

		//check if the robot pushes a box
		else if (board.at(newPos.x, newPos.y) == 'O') {
			//we need to iterate over all boxes in the line to determine if they are blocked by a wall
			Point boxCheck = newPos;
			while (board.at(boxCheck.x, boxCheck.y) == 'O')
				boxCheck = boxCheck + dir;
			//once we are no longer iterating over boxes check what space is after the push line
			//if it is an empty space then push the boxes and move the robot. If it is anything else do nothing
			if (board.at(boxCheck.x, boxCheck.y) == '.') {
				board.set(boxCheck.x, boxCheck.y, 'O');
				board.set(newPos.x, newPos.y, '@');
				board.set(robotPos.x, robotPos.y, '.');
				robotPos = newPos;
			}
		}

		//there is nothing in front of the robot so it moves forward
		else {
			board.set(robotPos.x, robotPos.y, '.');
			board.set(newPos.x, newPos.y, '@');
			robotPos = newPos;
		}
		//board.printBoard();
		//std::cout << "\n\n";
	}

	//sum the Goods Positioning System coodinates of all boxes
	size_t GPSSum = 0;
	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.at(x, y) == 'O')
				GPSSum += x + y * 100;
		}
	}

	std::cout << "Sum: " << GPSSum << '\n';

	return 0;
}

int puzzle2() {
	Board smallBoard("Inputs/Day15.txt", 50, 50);
	Point robotPos({ 0,0 });

	//widen the warehouse
	Board board('.', smallBoard.getWidth()*2, smallBoard.getHeight());
	for (int y = 0; y < smallBoard.getHeight(); y++) {
		for (int x = 0; x < smallBoard.getWidth(); x++) {
			if (smallBoard.at(x, y) == '#') {
				board.set(2 * x, y, '#');
				board.set(2 * x + 1, y, '#');
			}
			else if (smallBoard.at(x, y) == 'O') {
				board.set(2 * x, y, '[');
				board.set(2 * x + 1, y, ']');
			}
			else if (smallBoard.at(x, y) == '.') {
				board.set(2 * x, y, '.');
				board.set(2 * x + 1, y, '.');
			}
			else if (smallBoard.at(x, y) == '@') {
				board.set(2 * x, y, '@');
				board.set(2 * x + 1, y, '.');
			}
		}
	}

	/*
	smallBoard.printBoard();
	std::cout << '\n';
	board.printBoard();
	return 0;
	*/

	//find the robots position
	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.at(x, y) == '@') {
				robotPos.x = x;
				robotPos.y = y;

				//break the loop
				y = board.getHeight();
				break;
			}
		}
	}

	//parse the sequence
	std::ifstream inFile("Inputs/Day15.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	std::string inLine;
	bool readingCommands = false;
	std::vector<char> commands;
	while (std::getline(inFile, inLine)) {
		if (readingCommands) {
			for (char c : inLine) {
				if (c != '\n')
					commands.push_back(c);
			}
		}
		else if (inLine.length() == 0)
			readingCommands = true;
	}
	inFile.close();

	//board.printBoard();
	//std::cout << "\n";

	//preform commands
	for (char c : commands) {
		Point dir(0, 0);
		if (c == '<')
			dir.x = -1;
		else if (c == '>')
			dir.x = 1;
		else if (c == 'v')
			dir.y = 1;
		else if (c == '^')
			dir.y = -1;

		//std::cout << "Command: " << c << '\n';

		

		//move the robot and boxes
		Point newPos = robotPos + dir;
		//check if the robot would intersect a wall
		if (board.at(newPos.x, newPos.y) == '#')
			continue;

		//check if the robot pushes a box
		else if (board.at(newPos.x, newPos.y) == '[' || board.at(newPos.x, newPos.y) == ']') {
			std::queue<Point> boxesToCheck; //the left position of boxes
			std::stack<Point> checkedBoxes; //all boxes that have been checked. Box at the bottom is next to the bot
			//add the box directly in front of the robot to start the process
			if (board.at(newPos.x, newPos.y) == '[')
				boxesToCheck.push(newPos);
			else
				boxesToCheck.push(Point(newPos.x - 1, newPos.y));
			bool pushBlocked = false;
			while (!boxesToCheck.empty()) {
				Point box = boxesToCheck.front();
				checkedBoxes.push(box);
				boxesToCheck.pop();
				//add boxes that would be pushed by this box
				//calculation depends on the robot direction
				if (c == '<') {
					if (board.at(box + dir) == ']')
						boxesToCheck.push(box + (dir * 2));
					else if (board.at(box + dir) == '#') {
						pushBlocked = true;
						break;
					}
				}
				else if(c == '>') {
					if(board.at(box + (dir * 2)) == '[')
						boxesToCheck.push(box + (dir * 2));
					else if (board.at(box + (dir * 2)) == '#') {
						pushBlocked = true;
						break;
					}
				}
				//vertical directions can be treated the same
				else {
					if (board.at(box + dir) == '[') {
						boxesToCheck.push(box + dir);
					}
					if (board.at(box + dir) == ']') {
						boxesToCheck.push(box + dir + Point(-1, 0));
					}
					if (board.at(box + dir + Point(1, 0)) == '[') {
						boxesToCheck.push(box + dir + Point(1, 0));
					}
					if (board.at(box + dir) == '#' || board.at(box + dir + Point(1,0)) == '#') {
						pushBlocked = true;
						break;
					}
				}
			}
			if (!pushBlocked) {
				//update the box positions
				while (!checkedBoxes.empty()) {
					Point box = checkedBoxes.top();
					checkedBoxes.pop();
					board.set(box, '.');
					board.set(box + Point(1, 0), '.');
					board.set(box + dir, '[');
					board.set(box + dir + Point(1, 0), ']');
				}
				board.set(robotPos, '.');
				board.set(newPos, '@');
				robotPos = newPos;
			}
		}

		//there is nothing in front of the robot so it moves forward
		else {
			board.set(robotPos.x, robotPos.y, '.');
			board.set(newPos.x, newPos.y, '@');
			robotPos = newPos;
		}
		//board.printBoard();
		//std::cout << "\n" << std::endl;
	}

	//sum the Goods Positioning System coodinates of all boxes
	size_t GPSSum = 0;
	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.at(x, y) == '[')
				GPSSum += x + y * 100;
		}
	}

	std::cout << "Sum: " << GPSSum << '\n';

	return 0;
}