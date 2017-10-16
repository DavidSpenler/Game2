#ifndef ROOM
#define ROOM

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Room {
	public:
		Room();
		void make_sprite(Texture&,int,int,int,int,int);
		void add_door_connection(Room&);
		void add_stair_connection(Room*);
		void add_door_hit_box(FloatRect);
		void add_stair_hit_box(FloatRect);
		vector<Room*> door_connections;
		vector<Room*> stair_connections;
		vector<Sprite> doors;
		vector<Sprite> walls;
		vector<Sprite> floors;
		vector<Sprite> stairs;
		Sprite sprite;
		int floor;
		vector<int> stair_locs;
		vector<FloatRect> door_hit_boxes;
		vector<FloatRect> stair_hit_boxes;
};

#endif
