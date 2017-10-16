#ifndef FLOOR
#define FLOOR

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Floor {
	public:
		Floor();
		vector<vector<Sprite>> room_sprites;
		vector<vector<int>> rooms;
		vector<vector<int>> doors;
		vector<vector<vector<int>>> each_room;
		int num_rooms;
		vector<int> room_size;
		Sprite thissprite;
		
	private:
		Texture wall;
		Texture floor;
		Texture door;
		Texture stair;
		void create_rooms(vector<vector<int>>&, int&, vector<vector<vector<int>>>&);
		void create_doors(vector<vector<int>>&, vector<vector<int>>&, vector<vector<vector<int>>>&);
		void create_sprites(vector<vector<int>>&,vector<vector<int>>&,vector<vector<Sprite>>&,int&,Texture&);
};

#endif
