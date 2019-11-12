#pragma once

#include "Monster.h"
#include <stdlib.h>

class BeastNu :
	public Monster
{
public:
	BeastNu();
	BeastNu(int hp, int atk);
	~BeastNu();
	virtual void GenerateSequence() override;	// randomize a new set of sequence : sequence is 1-9
};