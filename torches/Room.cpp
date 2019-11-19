#include "Room.h"
#include <stdlib.h>

Room::Room()
{
	this->door = door;
	this->roomType = RoomType::TYPE_TORCHES;
	this->torchesLit = false;
	this->spawnMon = true;

	for (int i = 0; i < 5; i++)
	{
		monster.push_back(new GameObject());
	}
	
}

Room::Room(unsigned char door, int roomType, int numMon)
{
	this->door = door;
	this->roomType = roomType;
	this->torchesLit = false;
	this->spawnMon = spawnMon;

	if (numMon > 0) {
		spawnMon = 0;

		for (int i = 0; i < numMon; i++)
		{
			monster[i] = new GameObject();
		}
	}

}

int Room::getRoomType() {
	return this->roomType;
}

bool Room::haveMon() {
	return this->spawnMon;
}

bool Room::getTorches() {
	return torchesLit;
}

void Room::LitTorches(bool lit) {
	torchesLit = lit;
}

std::vector<GameObject*> Room::getMon() 
{
	return monster;
}

Room::~Room()
{
}
