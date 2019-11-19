#pragma once
#include "Phase.h"

#define ROOM_WIDTH 50
#define ROOM_HEIGHT 21

#define ROOM_NUMX 5
#define ROOM_NUMY 5

class PhaseMaze :
	public Phase
{
public:
	PhaseMaze();
	~PhaseMaze();
	virtual void OnUpdate(float dt, Screen& screen) override;

	void DrawRoom(Screen& screen, int roomId);
	void DrawMinimap(Screen& screen);
	static PhaseMaze* GetInstance();
	bool MinimapOn() const; // return m_TriggerMinimap

	void PlayerInput();

	void SpawnMon();
	void MoveMon();

	void UpdateDetectRange();
	void ClearDetectRange();
	void DrawMaze(Screen& screen);
	void Draw_Debug();

	void resetRoom();
private:
	
	Room* m_Rooms[ROOM_NUMY][ROOM_NUMX];
	static PhaseMaze* s_Instance;
	std::vector<int*> m_MapInfo;
	std::vector<int*> m_RoomInfo;

	Player* player;

	int currRoomX, currRoomY;

	int player_posX;
	int player_posY;
	char** map;
	bool** map_detect;
	bool debug_draw;

	bool m_TriggerMinimap;	// turn minimap on/off
};

