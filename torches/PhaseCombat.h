#pragma once
#include "Phase.h"
#include "Monster.h"
#include "Screen.h"

class PhaseCombat :
	public Phase
{
public:
	PhaseCombat();
	PhaseCombat(Monster* m);
	~PhaseCombat();	
	virtual void OnUpdate(float dt) override;
	static PhaseCombat* GetInstance();
	static PhaseCombat* GetInstance(Monster* m);
	void DrawSequence(Screen& screen); // draws monster's sequence on screen
private:
	static PhaseCombat* s_Instance;
	Monster* c_enemy;
};

