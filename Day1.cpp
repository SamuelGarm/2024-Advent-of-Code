#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int puzzle1();
int puzzle2();

int main(int argc, char* argv[]) {
	puzzle1();
}

int puzzle1() {
	std::ifstream inFile("Inputs/Day1.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	std::vector<int> list1;
	std::vector<int> list2;

	std::string myText;
	while (std::getline(inFile, myText)) {
		//split the line at the space
		list1.push_back(std::stoi(myText.substr(0, 5)));
		list2.push_back(std::stoi(myText.substr(8, 5)));
	}
	inFile.close();

	std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());

	int diff = 0;
	for (int i = 0; i < list1.size(); i++) {
		diff += abs(list1[i] - list2[i]);
	}
	std::cout << diff;
}


int puzzle2() {
	std::ifstream inFile("Inputs/Day1.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	std::vector<int> list1;
	std::vector<int> list2;

	std::string myText;
	while (std::getline(inFile, myText)) {
		//split the line at the space
		list1.push_back(std::stoi(myText.substr(0, 5)));
		list2.push_back(std::stoi(myText.substr(8, 5)));
	}
	inFile.close();

	//std::sort(list1.begin(), list1.end());
	//std::sort(list2.begin(), list2.end());

	int sim = 0;
	for (int i = 0; i < list1.size(); i++) {
		int count = std::count(list2.begin(), list2.end(), list1[i]);
		sim += list1[i] * count;
	}
	std::cout << sim;
}
