#pragma once
#include <vector>

#include "Monster.h"
#include "Screen.h"
#include "Game.h"
#include "Player.h"
#include "Room.h"

class Phase
{
	public:
		Phase();
		~Phase();
		virtual void OnUpdate(float dt) = 0;
};

