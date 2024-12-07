#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int puzzle1();
int puzzle2();
bool isSafe(const std::vector<int>& report);
bool isSafe2(const std::vector<int>& report);

int main(int argc, char* argv[]) {

	return puzzle2();
}

int puzzle1() {
	std::ifstream inFile("Inputs/Day2.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	int safeReports = 0;
	std::string myText;
	while (std::getline(inFile, myText)) {
		myText.push_back(' ');
		std::vector<int> list1;
		std::string num;
		//split the line at the space
		for (const char c : myText) {
			if (c != ' ') num += c;
			else {
				list1.push_back(std::stoi(num));
				num.clear();
			}
		}
		safeReports += isSafe(list1);
	}
	inFile.close();
	std::cout << safeReports << '\n';
	return 0;
}

bool isSafe(const std::vector<int>& report) {
	int direction = 0; //measures the total asscention/descent of the sequence
	for (int i = 1; i < report.size(); i++) { 
		direction += report[i - 1] < report[i] ? -1 : 1;
		if (abs(report[i - 1] - report[i]) < 1 || abs(report[i - 1] - report[i]) > 3) 
			return false;
	}
	if (abs(direction) != report.size() - 1)
		return false;
	return true;
}

int puzzle2() {
	std::ifstream inFile("Inputs/Day2.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	int safeReports = 0;
	std::string myText;
	while (std::getline(inFile, myText)) {
		myText.push_back(' ');
		std::vector<int> list1;
		std::string num;
		//split the line at the space
		for (const char c : myText) {
			if (c != ' ') num += c;
			else {
				list1.push_back(std::stoi(num));
				num.clear();
			}
		}
		safeReports += isSafe2(list1);
	}
	inFile.close();
	std::cout << safeReports << '\n';
	return 0;
}


bool inRange(int val, int min, int max) {
	return(val >= min && val <= max);
}

bool isSafe2(const std::vector<int>& report) {
	if (isSafe(report))
		return true;
	else {
		for (int i = 0; i < report.size(); i++) {
			std::vector<int> test;
			for (int j = 0; j < report.size(); j++) {
				if (j != i)
					test.push_back(report[j]);
			}
			if (isSafe(test))
				return true;
		}
	}
	return false;
}