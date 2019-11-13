#pragma once
#include "Entity.h"
#include "SequenceKeeper.h"

class Monster :
	public Entity
{
public:
	Monster();
	Monster(int hp, int atk);	// set hp, atk, isAlive = true
	~Monster();	
	SequenceKeeper m_SequenceKeeper;
	virtual void GenerateSequence() = 0;	// randomize a new set of sequence
};
