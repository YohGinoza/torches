#include "Room.h"



Room::Room()
{
	this->m_RoomId = 0;
	this->width = 0;
	this->height = 0;
	this->door = 0;
	
}

Room::Room(int id, int width, int height, int door, std::vector<Entity*> monsterBucket) {
	this->m_RoomId = id;
	this->width = width;
	this->height = height;
	this->door = door;

}


Room::~Room()
{
}
