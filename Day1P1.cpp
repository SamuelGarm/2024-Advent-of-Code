#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct location {
	bool searched = false;
	int ID = 0;
};

int main(int argc, char* argv[]) {
	std::ifstream inFile("Inputs/Day1P1.txt");
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
