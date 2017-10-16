#include "room.h"

Room::Room() {
	int i=0;
}

void Room::add_door_connection(Room& room) {
	Room* p_room = &room;
	Room::door_connections.push_back(p_room);
}

void Room::add_door_hit_box(FloatRect hit_box) {
	Room::door_hit_boxes.push_back(hit_box);
}

void Room::add_stair_connection(Room* room) {
	Room::stair_connections.push_back(room);
}

void Room::add_stair_hit_box(FloatRect hit_box) {
	Room::stair_hit_boxes.push_back(hit_box);
}

void Room::make_sprite(Texture& image,int w,int h,int x,int y,int type) {
	//image.loadFromFile("player.png",IntRect(0,0,w,h));
	image.setRepeated(true);
	sprite.setTexture(image);
	sprite.setTextureRect(IntRect(0,0,w,h));
	sprite.setPosition(x,y);
	switch(type) {
		case 0 : walls.push_back(sprite);
			break;
		case 1 : doors.push_back(sprite);
			break;
		case 2 : floors.push_back(sprite);
			break;
		case 3 : stairs.push_back(sprite);
			break;
	}
}
