#pragma once
#include "Phase.h"
#include "Monster.h"

class PhaseCombat :
	public Phase
{
public:
	PhaseCombat();
	~PhaseCombat();	
	virtual void OnUpdate(float dt) override;
	static PhaseCombat* GetInstance();
	void DrawSequence(); // draws monster's sequence on screen
private:
	static PhaseCombat* s_Instance();
};

