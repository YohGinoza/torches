#pragma once
#include "Phase.h"
#include "Monster.h"
#include "Sprite.h"

#define COMBAT_TIME_LIMIT 5

class PhaseCombat :
	public Phase
{
public:
	PhaseCombat();
	~PhaseCombat();	
	virtual void OnUpdate(float dt) override;
	static PhaseCombat* GetInstance();
	void DrawSequence(Screen& screen); // draws monster's sequence on screen
	void InitCombat(int, float);
private:
	static PhaseCombat* s_Instance;
	Monster* c_enemy;
	int index;
	float startTime;
};

