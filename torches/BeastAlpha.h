#pragma once

#include "Monster.h"

class BeastAlpha :
	public Monster
{
public:
	BeastAlpha();
	BeastAlpha(int hp, int atk);
	~BeastAlpha();
	virtual void GenerateSequence() override;	// randomize a new set of sequence : sequence is 'u' 'd' 'l' 'r'
};