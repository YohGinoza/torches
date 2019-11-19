#include <iostream>

#include "Monster.h"
#include "InputBuffer.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

Monster::Monster(int hp, int atk) {
	Hp = hp;
	AttackDamage = atk;
	isAlive = true;
}

void Monster::GenerateSequence() {
	
}


BeastAlpha::BeastAlpha()
{
	this->Hp = 10;
	this->AttackDamage = 10;
	this->isAlive = true;
	GenerateSequence();
}


BeastAlpha::BeastAlpha(int hp, int atk) {
	this->Hp = hp;
	this->AttackDamage = atk;
	this->isAlive = true;
	GenerateSequence();
}

BeastAlpha::~BeastAlpha()
{
}

void BeastAlpha::GenerateSequence() {
	for (int i = 0; i < m_SequenceKeeper.GetRange(); i++) {
		int randChar = rand() % 4;
		switch (randChar) {
		case 0: m_SequenceKeeper.SetSequenceAt(i, (int)KeyCode::KEY_UP);
			break;
		case 1: m_SequenceKeeper.SetSequenceAt(i, (int)KeyCode::KEY_DOWN);
			break;
		case 2: m_SequenceKeeper.SetSequenceAt(i, (int)KeyCode::KEY_LEFT);
			break;
		case 3: m_SequenceKeeper.SetSequenceAt(i, (int)KeyCode::KEY_RIGHT);
			break;
		}
	}
}

BeastNu::BeastNu()
{
	this->Hp = 10;
	this->AttackDamage = 10;
	this->isAlive = true;
	GenerateSequence();
}

BeastNu::BeastNu(int hp, int atk) {
	this->Hp = hp;
	this->AttackDamage = atk;
	this->isAlive = true;
	GenerateSequence();
}

BeastNu::~BeastNu()
{
}

void BeastNu::GenerateSequence() {
	for (int i = 0; i < m_SequenceKeeper.GetRange(); i++) {
		int randNum = (rand() % 9) + 1;
		m_SequenceKeeper.SetSequenceAt(i, randNum);

		std::cout << randNum << std::endl;
	}

}