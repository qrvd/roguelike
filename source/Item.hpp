#ifndef _ITEM_HPP_
#define _ITEM_HPP_

struct Item {
	enum Type { SCROLL, POTION, WEAPON };
	Type type;
    Vector pos;

	Item(Type t, Vector pos): type(t), pos(pos) {}
};

#endif
