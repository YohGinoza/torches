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
	SequenceKeeper<T> m_SequenceKeeper;
	virtual void GenerateSequence() = 0;	// randomize a new set of sequence
};

template <class T>
Monster<T>::Monster()
{
}

template <class T>
Monster<T>::~Monster()
{
}

template <class T>
Monster<T>::Monster(int hp, int atk) {
	Hp = hp;
	AttackDamage = atk;
	isAlive = true;
}

template <class T>
void Monster<T>::GenerateSequence() {

}
