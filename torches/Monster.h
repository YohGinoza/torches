#pragma once
#include "Entity.h"
#include "SequenceKeeper.h"

template<class T>
class Monster :
	public Entity
{
public:
	Monster();
	Monster(int hp, int atk);	// set hp, atk, isAlive = true
	~Monster();
	int GetHp() const;
	int GetAttackDamage() const;
	bool GetAliveStatus() const;
	SequenceKeeper<T> m_SequenceKeeper;
	virtual void GenerateSequence() = 0;// override;	// randomize a new set of sequence
protected:
	int Hp;
	int AttackDamage;
	bool isAlive;
};

