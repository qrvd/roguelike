#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_

struct Level;
struct Item;
#include "Common.hpp"

struct Monster {
	Level *level;
	List<Item*> items;
	String name;
	int health;
	Vector pos;

	Monster(Level *level, int health = 20, Vector pos = Vector());
    void move(int dx, int dy);
    void move(Vector delta);
};

#endif
