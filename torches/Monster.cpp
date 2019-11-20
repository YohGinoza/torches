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

BeastMix::BeastMix()
{
	this->Hp = 10;
	this->AttackDamage = 10;
	this->isAlive = true;
}


BeastMix::BeastMix(int hp, int atk) {
	this->Hp = hp;
	this->AttackDamage = atk;
	this->isAlive = true;
}

BeastMix::~BeastMix()
{
}

void BeastMix::GenerateSequence() {
	for (int i = 0; i < m_SequenceKeeper.GetRange(); i++) {
		int randNum = (rand() % 13) + 1;
		switch (randNum) {
		case 10: m_SequenceKeeper.SetSequenceAt(i, (int)KeyCode::KEY_UP);
			break;
		case 11: m_SequenceKeeper.SetSequenceAt(i, (int)KeyCode::KEY_DOWN);
			break;
		case 12: m_SequenceKeeper.SetSequenceAt(i, (int)KeyCode::KEY_LEFT);
			break;
		case 13: m_SequenceKeeper.SetSequenceAt(i, (int)KeyCode::KEY_RIGHT);
			break;
		default: m_SequenceKeeper.SetSequenceAt(i, randNum);
			break;
		}
	}
}