#pragma once
#include "Phase.h"
#include "MapGenerator.h"

#define ROOM_WIDTH 15
#define ROOM_HEIGHT 15

#define MON_PER_ROOM 7

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
	void CheckAround();
	void CheckTorches();

	void SpawnMon();
	void MoveMon();

	void UpdateDetectRange();
	void ClearDetectRange();
	void DrawMaze(Screen& screen);
	void Draw_Debug();
	void Draw_Minimap();

	void resetRoom();
private:
	MapGenerator* mapGen;
	Room* m_Rooms[MAP_HEIGHT][MAP_WIDTH];
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
	bool UpdateDraw;
	bool endBattle;

	bool m_TriggerMinimap;	// turn minimap on/off
};

