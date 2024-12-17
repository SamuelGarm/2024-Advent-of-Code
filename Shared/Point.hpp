#pragma once
struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {};
	bool operator==(const Point& other) const {
		return this->x == other.x && this->y == other.y;
	}

	bool operator<(const Point& other) const {
		if (x == other.x) return y < other.y;
		else return x < other.x;
	}

	Point operator+(const Point& other) const {
		return Point(x + other.x, y + other.y);
	}

	Point operator-(const Point& other) const {
		return Point(x - other.x, y - other.y);
	}

	Point operator*(const int other) const {
		return Point(x * other, y * other);
	}
};
