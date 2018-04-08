#ifndef _COMMON_HPP_
#define _COMMON_HPP_

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
  int x, y, w, h, right, bot;

  Rectangle(int x, int y, int w, int h): x(x), y(y), w(x), h(x), right(x+w), bot(y+h) {}
  Rectangle(Vector pos, Vector size): x(pos.x), y(pos.y), w(size.x), h(size.y), right(pos.x+size.x), bot(pos.y+size.y) {}
  Rectangle(int w, int h): x(0), y(0), w(w), h(h), right(w), bot(h) {}
  Rectangle(Vector size): x(0), y(0), w(size.x), h(size.y), right(size.x), bot(size.y) {}

  bool intersects(Rectangle b) {
      return (x >= b.x && right < b.right &&
              y >= b.y && bot < b.bot);
  }
};

#endif
