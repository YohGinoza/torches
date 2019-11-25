#pragma once
#include <stdlib.h>

#include "Entity.h"
#include "SequenceKeeper.h"

enum BeastType {
	BeastNum = 0,
	BeastAl,
	BeastHy
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

class BeastHybrid :
	public Monster
{
public:
	BeastHybrid();
	BeastHybrid(int hp, int atk);
	~BeastHybrid();
	virtual void GenerateSequence() override;	// randomize a new set of sequence : sequence is hybrid
};