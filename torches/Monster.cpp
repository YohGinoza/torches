#include "Monster.h"


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