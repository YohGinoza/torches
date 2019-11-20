#pragma once
#include <stdlib.h>

#include "Entity.h"
#include "SequenceKeeper.h"

enum BeastType {
	BeastNum = 0,
	BeastAl,
	BeastM
};

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


class BeastAlpha :
	public Monster
{
public:
	BeastAlpha();
	BeastAlpha(int hp, int atk);
	~BeastAlpha();
	virtual void GenerateSequence() override;	// randomize a new set of sequence : sequence is 'u' 'd' 'l' 'r'
};

class BeastNu :
	public Monster
{
public:
	BeastNu();
	BeastNu(int hp, int atk);
	~BeastNu();
	virtual void GenerateSequence() override;	// randomize a new set of sequence : sequence is 1-9
};

class BeastMix :
	public Monster
{
public:
	BeastMix();
	BeastMix(int hp, int atk);
	~BeastMix();
	virtual void GenerateSequence() override;
};