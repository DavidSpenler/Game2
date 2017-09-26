#include "player.h"
#include <iostream>

Player::Player(vector<Room>& a, Room*& b) {
	map = a;
	current_room = &b;
	image.loadFromFile("player.png");
	sprite.setTexture(image);
	sprite.setPosition(300,300);
	hit_box = sprite.getGlobalBounds();
}

void Player::set_move_x(int i) {
	move_x = i;
}

void Player::set_move_y(int i) {
	move_y = i;
}
	
void Player::move() {
	if (buffer==0) {
		sprite.move(move_x,0);
		hit_box = sprite.getGlobalBounds();
		for (int w=0;w<(*current_room)->walls.size();++w) { 
			if (hit_box.intersects((*current_room)->walls[w].getGlobalBounds())) {
				sprite.move(-move_x,0);
				//cout << "wall collision" << endl;
				break;
			}
		}
	}
	if (buffer==0) {
		sprite.move(0,move_y);
		hit_box = sprite.getGlobalBounds();
		for (int w=0;w<(*current_room)->walls.size();++w) { 
			if (hit_box.intersects((*current_room)->walls[w].getGlobalBounds())) {
				sprite.move(0,-move_y);
				//cout << "wall collision" << endl;
				break;
			}
		}
	}
	for (int d=0;d<(*current_room)->doors.size();++d) { 
		if (hit_box.intersects((*current_room)->door_hit_boxes[d]) && !Player::room_debounce && !hit_box.intersects((*current_room)->doors[d].getGlobalBounds())) {
			(*current_room) = (*current_room)->door_connections[d];
			//cout << "door collision" << endl;
			Player::room_debounce = true;
			break;
		}
		if (d==(*current_room)->doors.size()-1)
			Player::room_debounce = false;
	}
	//cout << Player::stair_debounce << endl;	
	Player::found_collision = false;
	for (int s=0;s<(*current_room)->stairs.size();++s) {
		if (hit_box.intersects((*current_room)->stair_hit_boxes[s])) {
			if (!Player::stair_debounce) {
				Player::stair_debounce = true;
				(*current_room) = (*current_room)->stair_connections[s];
			}	
			break;
		}
		if (s==(*current_room)->stairs.size()-1 && Player::stair_debounce) {
			Player::stair_debounce = false;
		}		
	}
	
	buffer=(buffer+1)%speed;
}
