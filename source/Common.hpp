#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <chrono>
#include <ctime>
#include <vector>
#include <map>
#include <string>
#include <cassert>

template <typename T, typename U>
class Map {
    std::map<T, U> entries;

public:
    Map(): entries() {}

    U operator[](T index) { return entries[index]; }
    void set(T index, U value) { entries[index] = value; }
    U get(T index) { return entries[index]; }
};

template <typename T>
struct List {
    std::vector<T> entries;
    List(): entries() {}
    List(size_t size, T initial): entries(size, initial) {}

    T operator[](int index) { return entries[index]; }
    void set(int index, T value) { entries[index] = value; }
    void push_back(T t) { entries.push_back(t); }
    size_t size() { return entries.size(); }
};

typedef std::string String;

#include <cmath>

struct Vector {
	int x, y;
	Vector(int x=0, int y=0): x(x), y(y) {}

	Vector operator+(Vector b) { return Vector(x+b.x, y+b.y); }
	Vector operator-(Vector b) { return Vector(x-b.x, y-b.y); }
	Vector operator*(int scale) { return Vector(x*scale, y*scale); }
	double length() { return sqrt(x*x + y*y); }
};

Vector mult(Vector a, Vector b) {
    return Vector(a.x * b.x, a.y * b.y);
}

struct Rectangle {
  int x, y, w, h, x2, y2;

  Vector center() {
    return Vector(round(float(x) + float(w)/2), round(float(y) + float(h)/2));
  }

  bool intersects(Rectangle other) {
      return (x <= other.x2 && x2 >= other.x &&
              y <= other.y2 && y2 >= other.y);
  }

  Rectangle(int _x, int _y, int _w, int _h): x(_x), y(_y), w(_w), h(_h), x2(_x+_w), y2(_y+_h) {}
  Rectangle(Vector pos, Vector size): x(pos.x), y(pos.y), w(size.x), h(size.y), x2(pos.x+size.x), y2(pos.y+size.y) {}
  Rectangle(Vector size): x(0), y(0), w(size.x), h(size.y), x2(0), y2(0) {}
};
#endif
