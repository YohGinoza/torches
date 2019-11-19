#pragma once
#include "Phase.h"
#include "Monster.h"

#define COMBAT_TIME_LIMIT 5
#define SPRITE_SPECIAL_OFFSET 8

class PhaseCombat :
	public Phase
{
public:
	PhaseCombat();
	~PhaseCombat();	
	virtual void OnUpdate(float dt, Screen& screen) override;
	static PhaseCombat* GetInstance();
	static PhaseCombat* GetInstance(Monster* m);
	void DrawCombatPhase(Screen& screen); // draws monster's sequence on screen
	void InitCombat(int, float);
private:
	static PhaseCombat* s_Instance;
	Monster* c_enemy;
	int index;
	float startTime;
};

