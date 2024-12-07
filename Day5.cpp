#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <regex>
#include <utility>
#include <stack>
#include <array>
#include <list>

int puzzle1();
//int puzzle2();
bool isPageOrderRight(const std::vector<int>& pages, const std::vector<std::pair<int, int>>& rules);
std::vector<int> fixPageOrder(const std::vector<int>& pages, const std::vector<std::pair<int, int>>& rules);

int main(int argc, char* argv[]) {
	return puzzle1();
}

int puzzle1() {
	std::ifstream inFile("Inputs/Day5.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}
	std::vector<std::pair<int, int>> rules;
	std::vector<std::vector<int>> pages;

	std::string myText;
	bool readingRules = true;
	while (std::getline(inFile, myText)) {
		if (myText.compare("") == 0) {
			readingRules = false; continue; }

		if (readingRules) {
			int delimPos = myText.find('|');
			int rule1 = std::atoi(myText.substr(0, delimPos).c_str());
			int rule2 = std::atoi(myText.substr(delimPos+1).c_str());
			rules.emplace_back(std::pair<int,int>(rule1, rule2));
		}
		else {
			std::vector<int> temp;
			while (true) {
				int delimPos = myText.find(',');
				if (delimPos == std::string::npos) delimPos = myText.length();
				temp.emplace_back(std::atoi(myText.substr(0, delimPos).c_str()));
				if (delimPos == myText.size()) break;
				myText = myText.substr(delimPos + 1);
			}
			pages.push_back(temp);
		}
	}
	
	//check each of the page sequences and see if they are valid
	int total = 0;
	int count = 0;
	for (auto& seq : pages) {
		std::cout << count << '/' << pages.size() << '\n';
		if (!isPageOrderRight(seq, rules)) {
			std::vector<int> fixed = fixPageOrder(seq, rules);
			if (fixed.size() == 0) return 2;
			total += fixed[fixed.size() / 2];
		}
		count++;
	}
	std::cout << total << std::endl;
	inFile.close();
	return 0;
}


/*
//returns a sequence that uses currentSequence as the base. Returns an empty vector if no valid sequence can be found
std::vector<int> buildPageOrder(const std::vector<int>& currentSquence, const std::vector<int>& toAppend, const std::vector<std::pair<int, int>>& rules) {
	//Assumptions: toAppend has at least one element. The currentSequence is valid
	
	//copy the page vector
	std::vector<int> test = std::vector<int>(currentSquence);

	//test appending each page to the sequence, if adding that page makes it invalid then terminate that branch of the search
	for (int i = 0; i < toAppend.size(); i++) {
		test.push_back(toAppend[i]);
		//only search further down this branch if adding toAppend[i] results in a valid sequence
		if (isPageOrderRight(test, rules)) {
			//If toAppend contains only one element then we know it has been appended to test and that the sequence at this point is valid
			if (toAppend.size() == 1)
				return test;

			//Keep searching the sequence space
			std::vector<int> pagesLeft;
			pagesLeft.reserve(toAppend.size() - 1);
			//make a copy of 'toAppend' without the page that has just been added
			for (int j = 0; j < toAppend.size(); j++) {
				if (i == j) continue;
				pagesLeft.push_back(toAppend[j]);
			}

			//recursive step
			std::vector<int> temp = buildPageOrder(test, pagesLeft, rules);
			//if temp is not empty then we can conclude it is a valid complete sequence
			if (temp.size() > 0) return temp;
		}
		test.pop_back();
	}

	//if we get to the end of the for loop that means that no valid sequence given the currentSequence as a base exists
	//return an empty vector to indicate failure
	return std::vector<int>();
}
*/
/*
std::vector<int> fixPageOrder(const std::vector<int>& pages, const std::vector<std::pair<int, int>>& rules) {
	struct permutation {
		short int toFix[32];
		short int toFixLeft = 0;
	};

	std::stack<permutation> stack;
	std::vector<int> result;

	permutation initial;
	initial.toFixLeft = pages.size();
	for (int i = 0; i < pages.size(); i++)
		initial.toFix[i] = pages[i];
	stack.push(initial);

	while (stack.top().toFixLeft > 0) {
		for (int i = 0; i < stack.top().toFixLeft; i++) {

		}
	}

}*/

std::vector<int> fixPageOrder(const std::vector<int>& pages, const std::vector<std::pair<int, int>>& rules) {
	std::vector<int> result;
	result.reserve(pages.size());
	//insert elements one by one in locations where no rules are violated
	for (int i = 0; i < pages.size(); i++) {
		int toPlace = pages[i];
		bool sucess = false;
		//find a spot to place it
		for (int j = 0; j <= i && !sucess; j++) {
			auto it = result.begin();
			result.insert(it + j, toPlace);
			if (isPageOrderRight(result, rules)) {
				sucess = true;
			}
			else {
				it = result.begin();
				result.erase(it + j);
			}
		}
	}
	return result;
}

//std::vector<int> fixPageOrder(const std::vector<int>& pages, const std::vector<std::pair<int, int>>& rules) {
//	retur/n buildPageOrder(std::vector<int>(), pages, rules);
//}

bool isPageOrderRight(const std::vector<int>& pages, const std::vector<std::pair<int, int>>& rules) {
	std::vector<int> pagesSeen;
	//go through page and check if that page causes a rule violation. If no violations are found the order is valid
	for (int pageNum : pages) {
		//check each rule to see if the current page appears on the left side of a rule
		for (const std::pair<int, int> rule : rules) {
			if (rule.first == pageNum) {
				//check if the right side of the rule has already been seen, if so then the rule is violated
				for (int seen : pagesSeen) {
					if (seen == rule.second) {
						return false;
					}
				}
			}
		}
		pagesSeen.push_back(pageNum);
	}
	return true;
}