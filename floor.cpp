#include "floor.h"

Floor::Floor() {
	create_rooms(rooms,num_rooms,each_room);
	create_doors(rooms,doors,each_room);
	create_sprites(rooms,doors,room_sprites,num_rooms,wall);
		
}

void Floor::create_rooms(vector<vector<int>>& f_rooms, int& f_num_rooms, vector<vector<vector<int>>>& f_each_room) {
	vector<vector<int>> rooms = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
	};
	int x = 0,next_x = 0;
	int y = 0,next_y = 0;
	int index = 1;
	int size,real_size;
	int n_choice;
	vector<vector<int>> this_room;
	vector<int> this_space;

	auto get_neighbours = [&rooms](int x, int y) {
		vector<vector<int>> neighbours;
		vector<int> neighbour;
		if (x+1 < 4 && rooms[y][x+1] == 0) {
			neighbour = {y,x+1};
			neighbours.push_back(neighbour);
		}
		if (x-1 > 0 && rooms[y][x-1] == 0) {
			neighbour = {y,x-1};
			neighbours.push_back(neighbour);
		}
		if (y+1 < 3 && rooms[y+1][x] == 0) {
			neighbour = {y+1,x};
			neighbours.push_back(neighbour);
		}
		if (y-1 > 0 && rooms[y-1][x] == 0) {
			neighbour = {y-1,x};
			neighbours.push_back(neighbour);
		}
		return neighbours;
	};

	auto advance_next = [&next_x,&next_y,&rooms]() {
		while (rooms[next_y][next_x] != 0) {
			next_x = (next_x+1)%4;
			if (next_x == 0)
				++next_y;
			if (next_y > 2) 
				break;
		}
	};

	while (y < 3 && index < 13) {
		this_room = {{y,x}};
		rooms[y][x] = index;
		size = rand()%3+1;
		real_size = 1;
		for (int s=1;s<size;++s) {
			vector<vector<int>> neighbours = get_neighbours(x,y);
			if (neighbours.size() == 0) {
				break;
			}
			n_choice = rand()%neighbours.size();
			x = neighbours[n_choice][1];
			y = neighbours[n_choice][0];
			this_space = {y,x};
			this_room.push_back(this_space);
			rooms[y][x] = index;
			++real_size;
		}
		++index;
		each_room.push_back(this_room);
		advance_next();
		x = next_x;
		y = next_y;	
	}
	f_num_rooms = index;
	f_rooms = rooms;
}

void Floor::create_doors(vector<vector<int>>& f_rooms, vector<vector<int>>& f_doors, vector<vector<vector<int>>>& f_each_room) {
	vector<int> connections = {1};
	vector<int> this_door;
	int x,y,n_doors;
	for (int r=0;r<f_each_room.size();++r) {
		for (int s=0;s<f_each_room[r].size();++s) {
			n_doors = 0;
			y = f_each_room[r][s][0];
			x = f_each_room[r][s][1];
			while (true)  {
				this_door = {};
				if (x<f_rooms[0].size()-1 && find(connections.begin(), connections.end(), f_rooms[y][x+1]) == connections.end()) {
					this_door = {y,x+1,y,x};
				}
				else if (x>1 && find(connections.begin(), connections.end(), f_rooms[y][x-1]) == connections.end()) {
					this_door = {y,x-1,y,x};

				}
				else if (y<f_rooms.size()-1 && find(connections.begin(), connections.end(), f_rooms[y+1][x]) == connections.end()) {
					this_door = {y+1,x,y,x};
				}
				else if (y>0 && find(connections.begin(), connections.end(), f_rooms[y-1][x]) == connections.end()) {
					this_door = {y-1,x,y,x};
				}

				if (this_door.size() != 0) {
					f_doors.push_back(this_door);
					connections.push_back(f_rooms[this_door[0]][this_door[1]]);
					++n_doors;
				}
				else {
					break;
				}
				if (n_doors == 2) {
					s=10;
					break;
				}	
			}
		}
	}
}

void Floor::create_sprites(vector<vector<int>>& f_rooms, vector<vector<int>>& f_doors, vector<vector<Sprite>>& f_room_sprites, int& f_num_rooms, Texture& f_image) {
	vector<int> door1,door2;
	vector<Sprite> room_sprite = {};
	for (int i=0;i<f_num_rooms;++i) {
		f_room_sprites.push_back(room_sprite);
	}

	auto make_sprite = [&f_room_sprites,&f_rooms,&f_image](string filename, int w, int h, int x, int y, int room_num) {
		Sprite sprite;
		f_image.loadFromFile("player.png",IntRect(0,0,w,h));
		f_image.setRepeated(true);
		sprite.setTexture(f_image);
		sprite.setTextureRect(IntRect(0,0,w,h));
		sprite.setPosition(x,y);
		f_room_sprites[room_num-1].push_back(sprite);
	};

	for (int y=0;y<f_rooms.size();++y) {
		for (int x=0;x<f_rooms[0].size();++x) {
			if (x+1 < f_rooms[0].size()) {
				if (f_rooms[y][x+1] != f_rooms[y][x]) {
					door1 = {y,x,y,x+1};
					door2 = {y,x+1,y,x};
					if (find(f_doors.begin(),f_doors.end(),door1) != f_doors.end() || find(f_doors.begin(),f_doors.end(),door2) != f_doors.end()) {
						//create edges of doorway
						make_sprite("player",50,50,(x+1)*250-50,250*y+50,f_rooms[y][x]);
						make_sprite("player",50,50,(x+1)*250-50,250*y+150,f_rooms[y][x]);
					}
					else {
						//create entire wall
						make_sprite("player",50,150,(x+1)*250-50,250*y+50,f_rooms[y][x]);
					}
				}
			}
			else {
				//create entire wall
				make_sprite("player",50,150,(x+1)*250-50,250*y+50,f_rooms[y][x]);
			}
			if (x-1 >= 0) {
				if (f_rooms[y][x-1] != f_rooms[y][x]) {
					door1 = {y,x,y,x-1};
					door2 = {y,x-1,y,x};
					if (find(f_doors.begin(),f_doors.end(),door1) != f_doors.end() || find(f_doors.begin(),f_doors.end(),door2) != f_doors.end()) {
						make_sprite("player",50,50,x*250,250*y+50,f_rooms[y][x]);
						make_sprite("player",50,50,x*250,250*y+150,f_rooms[y][x]);
					}
					else {
						make_sprite("player",50,150,x*250,250*y+50,f_rooms[y][x]);
					}
				}
			}
			else {
				make_sprite("player",50,150,x*250,250*y+50,f_rooms[y][x]);
			}
			if (y-1 >= 0) {
				if (f_rooms[y-1][x] != f_rooms[y][x]) {
					door1 = {y-1,x,y,x};
					door2 = {y,x,y-1,x};
					if (find(f_doors.begin(),f_doors.end(),door1) != f_doors.end() || find(f_doors.begin(),f_doors.end(),door2) != f_doors.end()) {
						make_sprite("player",50,50,x*250+50,250*y,f_rooms[y][x]);
						make_sprite("player",50,50,x*250+150,250*y,f_rooms[y][x]);
					}
					else {
						make_sprite("player",150,50,x*250+50,250*y,f_rooms[y][x]);
					}
				}
			}
			else {
				make_sprite("player",150,50,x*250+50,250*y,f_rooms[y][x]);
			}
			if (y+1 < f_rooms.size()) {
				if (f_rooms[y+1][x] != f_rooms[y][x]) {
					door1 = {y+1,x,y,x};
					door2 = {y,x,y+1,x};
					if (find(f_doors.begin(),f_doors.end(),door1) != f_doors.end() || find(f_doors.begin(),f_doors.end(),door2) != f_doors.end()) {
						make_sprite("player",50,50,x*250+50,250*(y+1)-50,f_rooms[y][x]);
						make_sprite("player",50,50,x*250+150,250*(y+1)-50,f_rooms[y][x]);
					}
					else {
						make_sprite("player",150,50,x*250+50,250*(y+1)-50,f_rooms[y][x]);
					}
				}
			}
			else {
				make_sprite("player",150,50,x*250+50,250*(y+1)-50,f_rooms[y][x]);
			}
			make_sprite("player",50,50,x*250,y*250,f_rooms[y][x]);
			make_sprite("player",50,50,x*250,(y+1)*250-50,f_rooms[y][x]);
			make_sprite("player",50,50,(x+1)*250-50,y*250,f_rooms[y][x]);
			make_sprite("player",50,50,(x+1)*250-50,(y+1)*250-50,f_rooms[y][x]);
		}
	}
}
