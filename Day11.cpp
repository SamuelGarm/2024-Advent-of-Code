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
#include <map>
#include <math.h>

int puzzle1();
//int puzzle2();

int main(int argc, char* argv[]) {
	return puzzle1();
}

struct Stones {
	std::map<size_t, size_t>* currentStep = &set1;
	std::map<size_t, size_t>* previousStep = &set2;

	void swap() {
		previousStep = currentStep;
		currentStep = previousStep == &set1 ? &set2 : &set1; //swap the currentStep for whatever it currently isn't
		currentStep->clear();
	}
private:
	std::map<size_t, size_t> set1;
	std::map<size_t, size_t> set2;
};

int puzzle1() {
	std::ifstream inFile("Inputs/Day11.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	//maps stone numbers to how many of them there are
	Stones stones;

	//load the file into the vector using a buffered read system
	std::string inText;
	while (std::getline(inFile, inText, ' ')) {
		size_t stone = std::stoull(inText);
		if (stones.currentStep->count(stone))
			(*stones.currentStep)[stone] += 1;
		else
			(*stones.currentStep)[stone] = 1;
	}

	//blink x times
	const size_t numBlinks = 1000;
	for (int i = 0; i < numBlinks; i++) {
		stones.swap();
		for (auto& [stone, count] : *stones.previousStep) {
			size_t numberLength = size_t(log10(stone) + 1);
			//for all stones of value 0 make them 1
			if (stone == 0) {
				(*stones.currentStep)[1] += count;
			} 
			//for all stones that have an even number of digits split them
			else if (numberLength % 2 == 0) {
				size_t shiftAmount = numberLength / 2;
				size_t upperValue = stone / pow(10, shiftAmount);
				size_t lowerValue = stone - (upperValue * pow(10,shiftAmount));
				(*stones.currentStep)[upperValue] += count;
				(*stones.currentStep)[lowerValue] += count;
			}
			//fallthrough case
			else {
				(*stones.currentStep)[stone * 2024] += count;
			}
			(*stones.previousStep)[stone] = 0;
		}
	}

	//count the stones
	size_t total = 0;
	for (const auto& [stone, count] : *stones.currentStep) {
		total += count;
	}
	std::cout << "Count: " << total << '\n';
	
	return 0;
}