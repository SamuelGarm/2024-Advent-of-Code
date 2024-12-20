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
#include <queue>
#include <limits>
#include "Shared/Board.hpp"
#include "Shared/Point.hpp"

int puzzle1();
//int puzzle2();

int main(int argc, char* argv[]) {
	return puzzle1();
}

enum Direction {
	UP, RIGHT, DOWN, LEFT
};

static Direction rotateCW(Direction dir) {
	if (dir == UP)
		return RIGHT;
	if (dir == RIGHT)
		return DOWN;
	if (dir == DOWN)
		return LEFT;
	if (dir == LEFT)
		return UP;
}

static Direction rotateCCW(Direction dir) {
	if (dir == UP)
		return LEFT;
	if (dir == RIGHT)
		return UP;
	if (dir == DOWN)
		return RIGHT;
	if (dir == LEFT)
		return DOWN;
}

struct Node {
	mutable size_t cost = ULLONG_MAX;
	Direction direction;
	Point location;
	mutable bool visited = false;

	Node() = delete;
	Node(Direction dir, Point loc) : direction(dir), location(loc) {};
	Node(Direction dir, Point loc, size_t cost) : direction(dir), location(loc), cost(cost) {};
	Node(const Node& other) {
		cost = other.cost;
		location = other.location;
		direction = other.direction;
		visited = other.visited;
	}

	bool operator==(const Node& other) const {
		bool res = location == other.location && direction == other.direction && cost == other.cost;
		return res;
	}

	bool operator<(const Node& other) const {
		if (location.x != other.location.x) return location.x < other.location.x;
		else if (location.y != other.location.y) return location.y < other.location.y;
		else return direction < other.direction;
	}
};

class NodeCompare {
public:
	bool operator() (const Node*& lhs, const Node*& rhs) const {
		return lhs->cost > rhs->cost;
	}
};

int puzzle1() {
	const int moveCost = 1;
	const int rotateCost = 1000;
	Board board("Inputs/Day16.txt", 141, 141);

	Point startPos(0,0);
	Point endPos(0,0);
	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.at(x, y) == 'S') {
				startPos = Point(x, y);
				board.set(x, y, '.');
			}
			if (board.at(x, y) == 'E') {
				endPos = Point(x, y);
				board.set(x, y, '.');
			}
		}
	}

	std::set<Node> nodes;
	std::priority_queue<const Node*, std::vector<const Node*>, NodeCompare> nodeHeap;

	//TEST TO ENSURE EXPECTED BEHAVIOUR
	/*
	Node n1(UP, Point(1,2));
	Node n2(RIGHT, Point(1,2));
	Node n3(DOWN, Point(1,2));
	Node n4(LEFT, Point(1, 2));
	Node n5(UP, Point(2, 2));
	Node n6(RIGHT, Point(2, 2));
	Node n7(DOWN, Point(2, 2));

	nodes.insert(n1);
	nodes.insert(n2);
	nodes.insert(n3);
	nodes.insert(n4);
	nodes.insert(n5);
	nodes.insert(n6);
	nodes.insert(n7);

	//insert the problem node
	Node n8(UP, Point(1, 1));
	nodes.insert(n8);
	*/
	/*
	//nodeHeap.push(n1);
	//nodeHeap.push(n2);
	//nodeHeap.push(n3);

	std::cout << nodeHeap.top().cost << '\n';
	nodeHeap.pop();
	std::cout << nodeHeap.top().cost << '\n';
	nodeHeap.pop();
	std::cout << nodeHeap.top().cost << '\n';
	*/

	

	//insert the start node
	auto ref = nodes.insert(Node(RIGHT, startPos, 0));
	nodeHeap.push((const Node*) & (*ref.first));
	
	while (!nodeHeap.empty()) {
		const Node* node = nodeHeap.top();
		nodeHeap.pop();
		node->visited = true;
		//check if we are at the end
		if (node->location == endPos) {
			std::cout << "END FOUND: " << node->cost << '\n';
			break;
		}
		Point dir(0, 0);
		if (node->direction == LEFT)
			dir.x = -1;
		else if (node->direction == RIGHT)
			dir.x = 1;
		else if (node->direction == DOWN)
			dir.y = 1;
		else if (node->direction == UP)
			dir.y = -1;

		//check if the node ahead can be updated
		Point nextLoc = node->location + dir;
		if (nextLoc.x >= 0 && nextLoc.x < board.getWidth() && nextLoc.y >= 0 && nextLoc.y < board.getHeight()) {
			if (board.at(nextLoc) != '#') {
				Node nextNode(node->direction, nextLoc);
				if (nodes.count(nextNode) == 0) {
					//need to make the node 
					auto ref = nodes.insert(nextNode);
					nodeHeap.push((const Node*)&(*ref.first));
				}

				//if moving through this node would be cheaper then update the cost of the next node
				if (nodes.find(nextNode)->cost > node->cost + moveCost)
					nodes.find(nextNode)->cost = node->cost + moveCost;
			}
		}

		Node nextNode(node->direction, node->location);
		nextNode.direction = rotateCW(node->direction);
		//handle the 2 rotations in place
		if (nodes.count(nextNode) == 0) {
			//need to make the node 
			auto ref = nodes.insert(nextNode);
			nodeHeap.push((const Node*)&(*ref.first));
		}
		if (nodes.find(nextNode)->cost > node->cost + rotateCost)
			nodes.find(nextNode)->cost = node->cost + rotateCost;

		nextNode = Node(node->direction, node->location);
		nextNode.direction = rotateCCW(node->direction);
		//handle the 2 rotations in place
		if (nodes.count(nextNode) == 0) {
			//need to make the node 
			auto ref = nodes.insert(nextNode);
			nodeHeap.push((const Node*)&(*ref.first));
		}
		if (nodes.find(nextNode)->cost > node->cost + rotateCost)
			nodes.find(nextNode)->cost = node->cost + rotateCost;
		
	}

	//std::cout << "Failed to find end\n";

	return 0;
}