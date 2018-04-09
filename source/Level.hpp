#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

struct Level {
	const Vector size;
	List<Tile*> tiles;
	List<Item*> items;
	List<Monster*> monsters;

	Level(int w, int h)
		: size(w, h), tiles(w * h, new Tile(Tile::VOID)), items(), monsters() {}
	Level(Vector size)
		: size(size), tiles(size.x * size.y, new Tile(Tile::VOID)), items(), monsters() {}

	Tile *getTile(int x, int y) {
		return tiles[x + y * size.x];
	}

	void setTile(int x, int y, Tile *t) {
		tiles.set(x + y * size.x, t);
	}

	void digRoom(Rectangle r) {
        for (int y = r.y; y <= r.y2; y++) {
            for (int x = r.x; x <= r.y2; x++) {
                Tile *t = getTile(x, y);
                t->passable = true;
                t->solid = false;
                t->type = Tile::AIR;
            }
        }
	}

	void tunnelX(int start, int end, int y) {
        for (int x = start; x <= end; x++) {
            Tile *t = getTile(x, y);
            t->passable = true;
            t->solid = false;
            t->type = Tile::AIR;
        }
	}

	void tunnelY(int start, int end, int x) {
        for (int y = start; y <= end; y++) {
            Tile *t = getTile(x, y);
            t->passable = true;
            t->solid = false;
            t->type = Tile::AIR;
        }
	}

	void generate() {
	    digRoom(Rectangle(20, 15, 30, 30));
	    digRoom(Rectangle(50, 15, 60, 30));
	}
};

#endif
