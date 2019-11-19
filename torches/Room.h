#pragma once

#include <vector>
#include "Entity.h"
#include "Item.h"

enum RoomType {
	TYPE_TORCHES = 0,
	TYPE_CHEST,
	TYPE_EMPTY
};

class Room : public Entity
{
public:
	Room();
	Room(int roomType, int numMon);
	int getRoomType();
	void setRoomType(int type);
	bool haveMon();
	bool getTorches();
	void LitTorches(bool lit);
	void setMonNull(int index);

	bool getWin();
	void setWinningTorches();

	std::vector<GameObject*> getMon();
	~Room();

private:
	int m_RoomId;
	unsigned char door;
	int roomType;
	bool spawnMon;
	bool winningTorches;
	bool torchesLit;
	std::vector<GameObject*> monster;
};

