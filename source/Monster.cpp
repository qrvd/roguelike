#include "Monster.hpp"
#include "Tile.hpp"
#include "Level.hpp"

Monster::Monster(Level *level, int health, Vector pos)
		: level(level), items(), health(health), pos(pos) {
    String names[5] = {"Bert", "Tim", "Igor", "Bob", "Sam"};
    name = String(names[rand() % 5]);
}

void Monster::move(int dx, int dy) {
    move(Vector(dx, dy));
    printf("I'm %s. I take a step!\n", name);
}

void Monster::move(Vector delta) {
    Vector dest = pos + delta;
    if (level) {
        Tile *t = level->getTile(dest);
        if (t && !t->blocked) {
            pos = dest;
            t->explored = true;
        }
    } else {
        pos = dest;
    }
}
