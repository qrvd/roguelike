#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "SDL/SDL.h"
#include "Monster.hpp"

struct Player {
	Monster *avatar;
};

Player player;

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
        if (t) {
            t->blocked = false;
            t->block_sight = false;
            t->type = Tile::AIR;
        }
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
        for (int x = r.x + 1; x < r.x2; x++) {
            for (int y = r.y+1; y <= r.y2; y++) {
                digTile(x, y);
                getTile(x,y)->type = Tile::DOOR;
            }
        }
	}

	void generate() {
	    int minroomsize = 6;
	    int maxroomsize = 10;
	    int maxrooms = 30;
	    std::vector<Rectangle> rooms;

	    srand(time(NULL));

	    for (int r = 0; r < maxrooms; r++) {
            int width = minroomsize + rand() % (maxroomsize - minroomsize);
            int height = minroomsize + rand() % (maxroomsize - minroomsize);
            int x = rand() % size.x;
            int y = rand() % size.y;

            Rectangle room(x, y, width, height);

            // Don't place if it intersects with any room.
            bool intersected = false;

            // Can't leave the map.
            if (room.x2 >= size.x || room.y2 >= size.y)
                intersected = true;

            for (int i = 0; i < rooms.size(); i++) {
                if (room.intersects(rooms[i])) {
                    intersected = true;
                    break;
                }
            }

            if (!intersected) {
                rooms.push_back(room);
                Vector center = room.center();
                digRoom(room);

                if (rooms.size() > 1) {
                    Vector previousCenter = rooms[rooms.size()-2].center();

                    if (rand() % 2 == 0) {
                        // vertical then horizontal
                        tunnelY(center.y, previousCenter.y, previousCenter.y);
                        tunnelX(center.x, previousCenter.x, previousCenter.x);
                    } else {
                        // horizontal then vertical
                        tunnelX(center.x, previousCenter.x, previousCenter.x);
                        tunnelY(center.y, previousCenter.y, previousCenter.y);
                    }
                }
            }
	    }
	}
};

#endif
