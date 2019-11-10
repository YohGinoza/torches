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
	virtual void GenerateSequence() = 0;	// randomize a new set of sequence
protected:
	int Hp;
	int AttackDamage;
	bool isAlive;
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
int Monster<T>::GetHp() const {
	return Hp;
}

template <class T>
int Monster<T>::GetAttackDamage() const {
	return AttackDamage;
}

template <class T>
bool Monster<T>::GetAliveStatus() const {
	return isAlive;
}

template <class T>
void Monster<T>::GenerateSequence() {

}
