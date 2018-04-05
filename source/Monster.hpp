#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_

struct Level;

struct Monster {
	Level *level;
	List<Item*> items;
	String name;
	int health;
	Vector pos;

	Monster(Level *level, String name, int health = 20, Vector pos = Vector())
		: level(level), items(), name(name), health(health), pos(pos) {}
};

#endif
