#pragma once
#include "Phase.h"
#include "MapGenerator.h"

#define ROOM_WIDTH 15
#define ROOM_HEIGHT 15

#define MON_PER_ROOM 7
#define DEFAULT_DETECT_RANGE 2
#define FIXED_OFFSET 8

class PhaseMaze :
	public Phase
{
public:
	PhaseMaze();
	~PhaseMaze();
	virtual void OnUpdate(float dt, Screen& screen) override;
	
	static PhaseMaze* GetInstance();

	void PlayerInput();
	void CheckAround();
	void CheckTorches();

	void SpawnMon();
	void MoveMon();

	void UpdateDetectRange();
	void ClearDetectRange();
	void DrawMinimap(Screen& screen);
	void DrawMaze(Screen& screen);
	void Draw_Debug();
	void Draw_Minimap();

	void TestPrintMiniMap(Screen& screen);

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

	int detectRange;
};

