#include "tile.h"

Tile::Tile() {
	image.loadFromFile("player.png");
	sprite.setTexture(image);
	sprite.setPosition(200,200);
 	hit_box = sprite.getGlobalBounds();
}
