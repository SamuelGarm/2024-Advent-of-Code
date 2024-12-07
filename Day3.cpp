#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>

int puzzle1();
int puzzle2();

int main(int argc, char* argv[]) {

	return puzzle2();
}

int puzzle1() {
	std::ifstream inFile("Inputs/Day3.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	int total = 0;
	std::string myText;
	//need to make the regex
	std::regex multRegex("mul\\(\\d+,\\d+\\)");
	while (std::getline(inFile, myText)) {
		auto matchesBegin = std::sregex_iterator(myText.begin(), myText.end(), multRegex);
		auto matchesEnd = std::sregex_iterator();
		for (std::sregex_iterator i = matchesBegin; i != matchesEnd; ++i) {
			std::smatch match = *i;
			std::string matchStr = match.str();
			//process the match
			//1. remove the mul( and )
			matchStr = matchStr.substr(4, matchStr.length() - 5);
			//2. Process the 2 numbers
			int delimPos = matchStr.find(',');
			int num1 = std::stoi(matchStr.substr(0, delimPos));
			int num2 = std::stoi(matchStr.substr(delimPos+1));
			total += num1 * num2;
		}
	}
	std::cout << total << std::endl;
	return 0;
}

int puzzle2() {
	std::ifstream inFile("Inputs/Day3.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	int total = 0;
	std::string myText;
	//need to make the regex
	std::regex multRegex("(mul\\(\\d+,\\d+\\))|(do\\(\\))|(don't\\(\\))");
	bool doMult = true;
	while (std::getline(inFile, myText)) {
		auto matchesBegin = std::sregex_iterator(myText.begin(), myText.end(), multRegex);
		auto matchesEnd = std::sregex_iterator();
		for (std::sregex_iterator i = matchesBegin; i != matchesEnd; ++i) {
			std::smatch match = *i;
			std::string matchStr = match.str();
			//process the match
			// 1. Check if it is a mult instruction
			if (matchStr.compare("do()") == 0)
				doMult = true;
			else if(matchStr.compare("don't()") == 0)
				doMult = false;
			else if(doMult) {
				//1. remove the mul( and )
				matchStr = matchStr.substr(4, matchStr.length() - 5);
				//2. Process the 2 numbers
				int delimPos = matchStr.find(',');
				int num1 = std::stoi(matchStr.substr(0, delimPos));
				int num2 = std::stoi(matchStr.substr(delimPos + 1));
				total += num1 * num2;
			}
		}
	}
	std::cout << total << std::endl;
	return 0;
}