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

#define ADD 0
#define MUL 1
#define CONC 2

int puzzle1();
int puzzle2();

unsigned long long EvaluateEquation(const std::string& equation);

int main(int argc, char* argv[]) {
	return puzzle2();
}

int puzzle1() {

	std::ifstream inFile("Inputs/Day7.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	unsigned long long int TotalCalibrationResult = 0;
	std::string myText;
	while (std::getline(inFile, myText)) {
		//std::cout << myText.c_str() << '\n';
		//load values into the data fields
		int delimPos = myText.find(':');
		char* end = nullptr;
		unsigned long long int target = std::strtoull(myText.substr(0, delimPos).c_str(), &end, 10);
		if (target == 0)
			return 1;
		//std::cout << "\tTarget: " << target << "\n\tValues: ";
		myText = myText.substr(delimPos + 2);

		std::vector<int> values;
		while (true) {
			delimPos = myText.find(' ');
			if (delimPos == std::string::npos) {
				values.push_back(std::atoi(myText.c_str()));
				break;
			}
			values.push_back(std::atoi(myText.substr(0, delimPos).c_str()));
			myText = myText.substr(delimPos + 1);
		}

		//this has no data from the file
		std::vector<int> operations(values.size() - 1, ADD); //operation at i is an operand for values at i and i+1 (eq = value[i] operand[i] value[i+1])
		
		//std::cout << "Testing the following combinations: \n";

		int status = 0; //0 = running, 1 = sucess, 2 = fail
		while (status == 0) {
			unsigned long long int total = values[0]; //we need to start with this value loaded in
			//std::cout << values[0] << ' ';
			//for (int i = 0; i < operations.size(); i++) {
			//	if (operations[i] == ADD) std::cout << '+';
			//	if (operations[i] == MUL) std::cout << '*';
			//	std::cout << ' ' << values[i + 1] << ' ';
			//}
		
			//evaluate the current total
			for (int i = 0; i < operations.size(); i++)
				if (operations[i] == ADD) total += values[i + 1];
				else if (operations[i] == MUL) total *= values[i + 1];

			if (operations.back() == MUL && total != target) {
				status = 2;
				//check if every instruction is a multiply, if not we keep iterating
				for (int i : operations)
					if (i != MUL)
						status = 0;
			}
			//std::cout << "= " << total << '\n';
			//we have the correct sequence
			if (total == target) {
				status = 1;
			}

			if (status != 0) break;

			//do a sort of binary ripple add except with math operations instead of 1 and 0 (and maybe more than 2 states) + -> *
				int pos = 0;
				bool overflow = true;
				while (pos < operations.size() && overflow) {
					operations[pos] += overflow;
					overflow = false;
					if (operations[pos] > MUL) {
						operations[pos] = ADD;
						overflow = true;
					}
					pos++;
				}

			
		}
		if (status == 1) {
			TotalCalibrationResult += target;
			std::cout << "SUCESS\n";
		}
		else {
			std::cout << "FAIL\n";
		}
	}
	std::cout << TotalCalibrationResult << '\n';
}



int puzzle2() {
	std::ifstream inFile("Inputs/Day7.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	unsigned long long int TotalCalibrationResult = 0;
	std::string myText;
	while (std::getline(inFile, myText)) {
		//load values into the data fields
		int delimPos = myText.find(':');
		char* end = nullptr;
		unsigned long long int target = std::strtoull(myText.substr(0, delimPos).c_str(), &end, 10);

		myText = myText.substr(delimPos + 2);

		std::vector<int> values;
		std::istringstream iss(myText);
		std::string token;
		while (std::getline(iss, token, ' '))
			values.push_back(std::atoi(token.c_str()));
				

		//this has no data from the file
		std::vector<int> operations(values.size() - 1, ADD); //operation at i is an operand for values at i and i+1 (eq = value[i] operand[i] value[i+1])

		int status = 0; //0 = running, 1 = sucess, 2 = fail
		while (status == 0) {
			unsigned long long int total = values[0]; //we need to start with this value loaded in

			//evaluate the current total
			for (int i = 0; i < operations.size(); i++) {
				if (operations[i] == ADD) {
					//test if the value will overflow
					if (values[i + 1] > std::numeric_limits<unsigned long long int>::max() - total) {
						status = 2;
						break;
					}
					total += values[i + 1];
				}
				else if (operations[i] == MUL) {
					//make sure both operands are not 0, if one is 0 then no overflow check is needed
					if(total == 0 || values[i+1] == 0)
						total *= values[i + 1];
					//check if the multiplication will overflow
					else if (total > std::numeric_limits<unsigned long long int>::max() / values[i+1]) {
						status = 2;
						break;
					}
					total *= values[i + 1];
				}
				else if (operations[i] == CONC) {
					std::string leftVal = std::to_string(total);
					std::string rightVal = std::to_string(values[i + 1]);
					total = std::strtoull(std::string(leftVal + rightVal).c_str(), &end, 10);
					//test if this value is to large to be held in a ulli type
					if (errno == ERANGE) {
						//abandon trying to evaluate this equation further
						status = 2;
						errno = 0; //reset the flag
						break;
					}
				}
			}

			if (operations.back() == CONC && total != target) {
				status = 2;
				//check if every instruction is a multiply, if not we keep iterating
				for (int i : operations)
					if (i != CONC)
						status = 0;
			}
			//std::cout << "= " << total << '\n';
			//we have the correct sequence
			if (total == target) {
				status = 1;
			}

			if (status != 0) break;

			//do a sort of binary ripple add except with math operations instead of 1 and 0 (and maybe more than 2 states) + -> *
			int pos = 0;
			bool overflow = true;
			while (pos < operations.size() && overflow) {
				operations[pos] += overflow;
				overflow = false;
				if (operations[pos] > CONC) {
					operations[pos] = ADD;
					overflow = true;
				}
				pos++;
			}
		}
		if (status == 1) {
			TotalCalibrationResult += target;
			std::cout << "SUCESS\n";
		}
		else {
			std::cout << "FAIL\n";
		}
	}
	std::cout << TotalCalibrationResult << '\n';
}

unsigned long long EvaluateEquation(const std::string& equation)
{
	std::vector<int> values;
	std::vector<int> operations;
	
	//tokenize the string
	std::istringstream iss(equation);
	std::string token;
	std::vector<std::string> tokens;
	while (std::getline(iss, token, ' ')) {
		
	}
	

	unsigned long long int total = values[0];
	//evaluate the total
	for (int i = 0; i < operations.size(); i++)
		if (operations[i] == ADD) total += values[i + 1];
		else if (operations[i] == MUL) total *= values[i + 1];
	return 0;
}
