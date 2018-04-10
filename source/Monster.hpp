#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_

#include "Tile.hpp"
#include "Level.hpp"

struct Monster {
	Level *level;
	List<Item*> items;
	String name;
	int health;
	Vector pos;

	Monster(Level *level, String name, int health = 20, Vector pos = Vector())
		: level(level), items(), name(name), health(health), pos(pos) {}

    void move(int dx, int dy) {
        move(Vector(dx, dy));
    }

    void move(Vector delta) {
        Vector dest = pos + delta;
        if (level) {
            Tile *t = level->getTile(dest);
            if (t && !t->blocked) {
                pos = dest;
            }
        } else {
            pos = dest;
        }
    }
};

#endif
