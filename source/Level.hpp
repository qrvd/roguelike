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
		assert(x < size.x && x >= 0);
		assert(y < size.y && y >= 0);
		return tiles[x + y * size.x];
	}

	void setTile(int x, int y, Tile *t) {
		assert(x < size.x && x > 0);
		assert(y < size.y && y > 0);
		tiles.set(x + y * size.x, t);
	}
};

#endif
