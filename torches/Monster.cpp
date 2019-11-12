#include "Monster.h"

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