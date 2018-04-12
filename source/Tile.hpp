#ifndef _TILE_HPP_
#define _TILE_HPP_

struct Item;

struct Tile {
	enum Type { VOID, AIR, WALL, DOOR, TRAP, BUSH };
	Type type;

	bool blocked;
	bool block_sight;
	bool explored;

	Tile(Type t = VOID, bool blocked = false, bool block_sight = false): type(t), blocked(blocked), block_sight(true), explored(false) {
	}
};

#endif
