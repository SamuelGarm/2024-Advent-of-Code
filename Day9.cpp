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
#include <list>

int puzzle1();
int puzzle2();

int main(int argc, char* argv[]) {
	return puzzle2();
}

int puzzle1() {
	std::ifstream inFile("Inputs/Day9.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	//calculate how many characters are in the file. This is an UPPER limit and may include extreneous characters like \n that won't be parsed.
	//However this is still worth it to allow a single vector memory allocation instead of multiple allocations and copys as the vector grows
	inFile.seekg(0, inFile.end);
	size_t characterCount = inFile.tellg()/sizeof(char);
	inFile.seekg(0, inFile.beg);
	std::cout << "Input contains " << characterCount << " characters\n";

	if (characterCount == 0)
		return 0;

	std::vector<char> dataLayout;
	dataLayout.reserve(characterCount);

	//some variables we will need to calculate as the file is loaded into RAM
	size_t realLayoutSpace = 0; //how many characters will be needed when the data is expanded as per the problem

	//load the file into the vector using a buffered read system
	const int bufferSize = 128;
	char inBuff[bufferSize];
	while (!inFile.eof()) {
		inFile.read(inBuff, bufferSize);
		size_t readCount = inFile.gcount();
		size_t charactersRead = inFile.gcount();
		for (int i = 0; i < charactersRead; i++) {
			//make sure it is a numeral character
			if (inBuff[i] >= '0' && inBuff[i] <= '9')
				dataLayout.push_back(inBuff[i] - '0'); //convert it to a value 
		}
	}

	//figure out what the value of the last data block is
	//data values alternate between 'file length' and 'free space length'
	//so length=ID would map as follows, 0 = 0, 1 = 0, 2 = 0, 3 = 1, 4 = 1
	size_t lastFileID = (dataLayout.size()-1) / 2; //truncates to an int

	//set up 2 iterators (although we need index so it is index values), an empty space iterator and a dataMove iterator
	size_t leftIt = 0;
	auto rightIt = dataLayout.size() - 1;
	//we don't need to actually rearrange the data to calculate the checksum, it can be determined in linear time!
	//Doing this will probably mess me over for part 2 but I think the apporach is neat!
	size_t currentID = 0; 
	bool readingFile = true;
	size_t virtualPos = 0;//the position we would be at if the file was 'expanded'
	unsigned long long int checksum = 0; //learnt my lesson about assuming checksums won't be big numbers...
	while (leftIt <= rightIt) {
		const char val = (dataLayout[leftIt]);
		//if we are reading from the file perform the checksum calculation
		if (readingFile) {
			for (int i = 0; i < val; i++) {
				size_t result = (virtualPos * currentID);
				checksum += result;
				virtualPos++;
			}
			currentID++;
			leftIt++;
			readingFile = !readingFile;
		}
		else {
			//'move' data from the end to fill up this spot
			//determine how much data to move
			int toMove = std::min(dataLayout[rightIt], val);
			//add the 'moved' data to the checksum
			for (int i = 0; i < toMove; i++) {
				size_t result = (virtualPos * lastFileID);
				checksum += result;
				virtualPos++;
			}
			//remove the 'moved' data from the end
			dataLayout[rightIt] -= toMove;
			dataLayout[leftIt] -= toMove;
			if (dataLayout[rightIt] == 0) {
				//all data has been compacted to the left
				rightIt -= 2;
				lastFileID--;
			}
			if(dataLayout[leftIt] == 0) {
				leftIt++;
				readingFile = !readingFile;
			}
			
		}
		
	}

	std::cout << checksum << '\n';
	return 0;
}

int puzzle2() {
	std::ifstream inFile("Inputs/Day9.txt");
	if (!inFile.is_open()) {
		std::cerr << "Error opening the file!";
		return 1;
	}

	//calculate how many characters are in the file. This is an UPPER limit and may include extreneous characters like \n that won't be parsed.
	//However this is still worth it to allow a single vector memory allocation instead of multiple allocations and copys as the vector grows
	inFile.seekg(0, inFile.end);
	size_t characterCount = inFile.tellg() / sizeof(char);
	inFile.seekg(0, inFile.beg);
	std::cout << "Input contains " << characterCount << " characters\n";

	if (characterCount == 0)
		return 0;

	struct MemoryBlock {
		char dataSize = 0; 
		size_t ID = 0;
		bool isEmpty = true;
		MemoryBlock(char _dataSize, size_t _ID, bool _isEmpty) : dataSize(_dataSize), ID(_ID), isEmpty(_isEmpty) {};
	};

	std::list<MemoryBlock> dataLayout;

	//some variables we will need to calculate as the file is loaded into RAM
	size_t realLayoutSpace = 0; //how many characters will be needed when the data is expanded as per the problem

	//load the file into the vector using a buffered read system
	const int bufferSize = 128;
	char inBuff[bufferSize];
	size_t ID = 0;
	bool isFile = true;
	while (!inFile.eof()) {
		inFile.read(inBuff, bufferSize);
		size_t readCount = inFile.gcount();
		size_t charactersRead = inFile.gcount();
		for (int i = 0; i < charactersRead; i++) {
			//make sure it is a numeral character
			if (inBuff[i] >= '0' && inBuff[i] <= '9') {
				if (isFile) {
					dataLayout.push_back(MemoryBlock(inBuff[i] - '0', ID, false)); //convert it to a value
					ID++;
				}
				else {
					dataLayout.push_back(MemoryBlock(inBuff[i] - '0', 0, true));
				}
				isFile = !isFile;
			}
		}
	}

	//compact the data
	for (auto& it = dataLayout.rbegin(); it != dataLayout.rend(); it++) {
		if ((*it).isEmpty) continue;
		for (auto& findEmpty_it = dataLayout.begin(); findEmpty_it != it.base() --; findEmpty_it++) {
			if ((*findEmpty_it).isEmpty && (*findEmpty_it).dataSize >= (*it).dataSize) {
				//figure out if we need to split the free memory block
				if ((*findEmpty_it).dataSize == (*it).dataSize) {
					//no split, copy the data and mark the old as empty
					(*findEmpty_it).dataSize = (*it).dataSize;
					(*findEmpty_it).ID = (*it).ID;
					(*findEmpty_it).isEmpty = false;
				}
				else {
					//split
					dataLayout.insert(findEmpty_it, MemoryBlock(*it));
					(*findEmpty_it).dataSize -= (*it).dataSize;
				}
				(*it).isEmpty = true;

				////print out the output
				//for (const auto& elm : dataLayout) {
				//	for (int i = 0; i < elm.dataSize; i++)
				//		if (elm.isEmpty) std::cout << '.';
				//		else std::cout << elm.ID;
				//}
				//std::cout << '\n';

				break;
			}
		}
	}

	//calculate the checksum
	size_t checksum = 0;
	size_t virtualPointer = 0;
	for (const auto& elm : dataLayout)
		if (elm.isEmpty)
			virtualPointer += elm.dataSize;
		else 
			for (int i = 0; i < elm.dataSize; i++) {
				checksum += virtualPointer * elm.ID;
				virtualPointer++;
			}
	std::cout << checksum;

	return 0;
}