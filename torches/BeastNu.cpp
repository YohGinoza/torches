#include "BeastNu.h"
#include <cstdlib>

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
