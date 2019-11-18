#include "Room.h"
#include <stdlib.h>



Room::Room()
{
	this->m_RoomId = 0;
	this->width = 73;
	this->height = 57;
	this->door = 1;
	this->torch = false;
	this->spawnMon = false;
	for (int i = 0; i < monster.size(); i++){
		monster[i] = nullptr;
	}
	
}

Room::Room(int id, int width, int height, int door, bool torch, bool spawnMon, std::vector<Entity*> monsterBucket) {
	this->m_RoomId = id;
	this->width = width;
	this->height = height;
	this->door = door;
	this->torch = torch;
	this->spawnMon = spawnMon;
	for (int i = 0; i < monsterBucket.size(); i++) {
		monster[i] = monsterBucket[i];
	}

}

bool Room::haveTorch() {
	return this->torch;
}

bool Room::haveMon() {
	return this->spawnMon;
}

Room::~Room()
{
}
