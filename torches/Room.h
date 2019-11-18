#pragma once

#include <vector>
#include "Entity.h"
#include "Item.h"

class Room : public Entity
{
public:
	Room();
	Room(int id, int width, int height, int door, bool torch, bool spawnMon, std::vector<Entity*> monsterBucket);
	bool haveTorch();
	bool haveMon();
	~Room();
private:
	int m_RoomId;
	int width;
	int height;
	int door;
	bool torch;
	bool spawnMon;
	std::vector<Entity*> monster;
};

