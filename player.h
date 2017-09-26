#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "tile.h"
#include "room.h"

using namespace std;
using namespace sf;

class Player {
	public:
		Player(vector<Room>&,Room*&);
		Sprite sprite;
		void set_move_x(int);
		void set_move_y(int);		
		void move();
		FloatRect hit_box;
	private:
		Texture image;	
		int x,y;
		int move_x = 0;
		int move_y = 0;
		int buffer = 0;
		int speed = 2;
		bool room_debounce = false;
		int stair_debounce = 0;
		bool found_collision = false;
		vector<Room> map;
		Room** current_room;
};
		
#endif
