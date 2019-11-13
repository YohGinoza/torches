#pragma once
#include <vector>
#include "Phase.h"
#include "Screen.h"
#include "Room.h"
#include "Game.h"

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
private:
	std::vector<Room*> m_Rooms;
	static PhaseMaze* s_Instance;
	std::vector<int*> m_MapInfo;
	std::vector<int*> m_RoomInfo;
	bool m_TriggerMinimap;	// turn minimap on/off
};

