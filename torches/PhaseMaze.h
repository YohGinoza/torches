#pragma once
#include <vector>
#include "Phase.h"
#include "Screen.h"
#include "Room.h"
#include "Game.h"

#define room_width 25
#define room_height 21

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

	void UpdateDetectRange();
	void ClearDetectRange();
	void Draw_Debug();
private:
	std::vector<Room*> m_Rooms;
	static PhaseMaze* s_Instance;
	std::vector<int*> m_MapInfo;
	std::vector<int*> m_RoomInfo;

	int player_posX;
	int player_posY;
	char** map;
	bool** map_detect;
	bool debug_draw;

	bool m_TriggerMinimap;	// turn minimap on/off
};

