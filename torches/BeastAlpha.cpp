#include "BeastAlpha.h"


BeastAlpha::BeastAlpha()
{
}


BeastAlpha::BeastAlpha(int hp, int atk) {
	this->Hp = hp;
	this->AttackDamage = atk;
	this->isAlive = true;
}

BeastAlpha::~BeastAlpha()
{
}

void BeastAlpha::GenerateSequence() {
	for (int i = 0; i < m_SequenceKeeper.GetRange(); i++) {
		int randChar = rand() % 4;
		switch (randChar) {
		case 0: m_SequenceKeeper.SetSequenceAt(i, 'u');
			break;
		case 1: m_SequenceKeeper.SetSequenceAt(i, 'd');
			break;
		case 2: m_SequenceKeeper.SetSequenceAt(i, 'l');
			break;
		case 3: m_SequenceKeeper.SetSequenceAt(i, 'r');
			break;
		}
	}
}
