#pragma once

#include <vector>
#include "Entity.h"
#include "Item.h"

class Room : public Entity
{
public:
	Room();
	Room(int id, int width, int height, int door, std::vector<Entity*> monsterBucket);
	~Room();
private:
	int m_RoomId;
};

