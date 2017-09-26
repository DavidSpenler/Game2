#ifndef TILE
#define TILE

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Tile {
	public:
		Tile();
		Sprite sprite;
		FloatRect hit_box;
	private:
		Texture image;
};

#endif
