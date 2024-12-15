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
int puzzle2();

int main(int argc, char* argv[]) {
	return puzzle2();
}

int puzzle1() {
	std::ifstream inFile("Inputs/Day13.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	size_t totalSpent = 0;

	std::string inLine;
	while (std::getline(inFile, inLine)) {
		if (inLine.length() == 0) continue;
		std::string command_A = inLine.substr(inLine.find(':')+1);

		std::getline(inFile, inLine);
		std::string command_B = inLine.substr(inLine.find(':')+1);
		
		std::getline(inFile, inLine);
		std::string command_Prize = inLine.substr(inLine.find(':')+1);

		//parse the commands to numerical values
		double A[2] = {std::stoll(command_A.substr(2, command_A.find(','))), std::stoll(command_A.substr(command_A.find(',')+3)) };
		double  B[2] = {std::stoll(command_B.substr(2, command_B.find(','))), std::stoll(command_B.substr(command_B.find(',')+3)) };
		double C[2] = { std::stoll(command_Prize.substr(3, command_Prize.find(','))), std::stoll(command_Prize.substr(command_Prize.find(',')+4)) };

		//perform simple linear equation tA+sB=C
		double s = (C[0] * A[1] - C[1] * A[0]) / (B[0] * A[1] - B[1] * A[0]);
		double t = (C[0] - s * B[0]) / A[0];

		//check if they are integers or not (approximating...)
		if (s - (long long int)s > 0.0000001)
			continue;
		if (t - (long long int)t > 0.0000001)
			continue;

		size_t numTokens = t * 3 + s;
		totalSpent += numTokens;
		std::cout << numTokens << '\n';
	}
	std::cout << "Total: " << totalSpent << '\n';
}


int puzzle2() {
	std::ifstream inFile("Inputs/Day13.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	size_t totalSpent = 0;

	std::string inLine;
	while (std::getline(inFile, inLine)) {
		if (inLine.length() == 0) continue;
		std::string command_A = inLine.substr(inLine.find(':') + 1);

		std::getline(inFile, inLine);
		std::string command_B = inLine.substr(inLine.find(':') + 1);

		std::getline(inFile, inLine);
		std::string command_Prize = inLine.substr(inLine.find(':') + 1);

		//parse the commands to numerical values
		double A[2] = { std::stoll(command_A.substr(2, command_A.find(','))), std::stoll(command_A.substr(command_A.find(',') + 3)) };
		double  B[2] = { std::stoll(command_B.substr(2, command_B.find(','))), std::stoll(command_B.substr(command_B.find(',') + 3)) };
		double C[2] = { std::stoll(command_Prize.substr(3, command_Prize.find(','))), std::stoll(command_Prize.substr(command_Prize.find(',') + 4)) };

		//add the massive offset
		C[0] += 10000000000000;
		C[1] += 10000000000000;

		//perform simple linear equation tA+sB=C
		double s = (C[0] * A[1] - C[1] * A[0]) / (B[0] * A[1] - B[1] * A[0]);
		double t = (C[0] - s * B[0]) / A[0];

		//check if they are integers or not (approximating...)
		if (s - (long long int)s > 0.0000001)
			continue;
		if (t - (long long int)t > 0.0000001)
			continue;

		size_t numTokens = t * 3 + s;
		totalSpent += numTokens;
		std::cout << numTokens << '\n';
	}
	std::cout << "Total: " << totalSpent << '\n';
}