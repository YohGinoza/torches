#pragma once
#include <vector>
#include "Phase.h"
#include "Screen.h"
#include "Room.h"
#include "Game.h"
#include "Player.h"

#define room_width 15
#define room_height 15

#define room_numX 5
#define room_numY 5

class PhaseMaze :
	public Phase
{
public:
	PhaseMaze();
	~PhaseMaze();
	virtual void OnUpdate(float dt) override;

	void DrawRoom(Screen& screen, int roomId);
	void DrawMinimap(Screen& screen);
	static PhaseMaze* GetInstance();
	bool MinimapOn() const; // return m_TriggerMinimap

	void PlayerInput();
	
	void SpawnMon();
	void MoveMon();

	void UpdateDetectRange();
	void ClearDetectRange();
	void Draw_Debug();
	void resetRoom();
private:
	
	Room* m_Rooms[room_numY][room_numX];
	static PhaseMaze* s_Instance;
	std::vector<int*> m_MapInfo;

	Player* player;

	int player_posX;
	int player_posY;

	int currRoomX, currRoomY;

	char** map;
	bool** map_detect;
	bool debug_draw;

	bool m_TriggerMinimap;	// turn minimap on/off
};

