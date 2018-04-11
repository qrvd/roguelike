#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "SDL/SDL.h"

struct Level {
	const Vector size;
	List<Tile*> tiles;
	List<Item*> items;
	List<Monster*> monsters;

	void createMap() {
        for (int y = 0; y < size.y; y++)
            for (int x = 0; x < size.x; x++)
                tiles.push_back(new Tile(Tile::VOID, true, false));
	}

	Level(int w, int h)
		: size(w, h), tiles(), items(), monsters() { createMap(); }
	Level(Vector size)
		: size(size), tiles(), items(), monsters() { createMap(); }

	Tile *getTile(Vector pos) {
	    if (pos.x < size.x && pos.x >= 0 && pos.y < size.y && pos.y >= 0) {
            return tiles[pos.x + pos.y * size.x];
	    } else {
            return NULL;
		}
	}

	Tile *getTile(int x, int y) {
	    return getTile(Vector(x, y));
	}

	void setTile(int x, int y, Tile *t) {
		tiles.set(x + y * size.x, t);
	}

	void digTile(int x, int y) {
        Tile *t = getTile(x, y);
        t->blocked = false;
        t->block_sight = false;
        t->type = Tile::AIR;
	}

	void tunnelX(int start, int end, int y) {
	    if (start > end) {
            int temp = start;
            start = end;
            end = temp;
	    }
        for (int x = start; x <= end; x++) {
            digTile(x, y);
        }
	}

	void tunnelY(int start, int end, int x) {
	    if (start > end) {
            int temp = start;
            start = end;
            end = temp;
	    }
        for (int y = start; y <= end; y++) {
            digTile(x, y);
        }
	}

	void digRoom(Rectangle r) {
        for (int x1 = r.x + 1; x1 < r.x2; x1++) {
            for (int y1 = r.y + 1; y1 < r.y2; y1++) {
                digTile(x1, y1);
            }
        }
	}

	void generate() {
	    int minroomsize = 6;
	    int maxroomsize = 10;
	    int maxrooms = 30;
	    std::vector<Rectangle> rooms;
	    tunnelX(25, 55, 23);
	    digRoom(Rectangle(20, 15, 10, 15));
	    digRoom(Rectangle(50, 15, 10, 15));
	}
};

#endif
