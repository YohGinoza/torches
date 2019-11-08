#pragma once

#include "Monster.h"

class BeastNu :
	public Monster<int>
{
public:
	BeastNu();
	BeastNu(int hp, int atk);
	~BeastNu();
	virtual void GenerateSequence() override;	// randomize a new set of sequence : sequence is 1-9
};

