#pragma once

#include "Monster.h"
#include <stdlib.h>

class BeastNu :
	public Monster<int>
{
public:
	BeastNu();
	BeastNu(int hp, int atk);
	~BeastNu();
	virtual void GenerateSequence() override;	// randomize a new set of sequence : sequence is 1-9
};

BeastNu::BeastNu()
{
}

BeastNu::BeastNu(int hp, int atk) {
	this->Hp = hp;
	this->AttackDamage = atk;
	this->isAlive = true;
}

BeastNu::~BeastNu()
{
}

void BeastNu::GenerateSequence() {
	for (int i = 0; i < m_SequenceKeeper.GetRange(); i++) {
		int randNum = (rand() % 9) + 1;
		m_SequenceKeeper.SetSequenceAt(i, randNum);
	}

}
