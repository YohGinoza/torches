#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include <stdlib.h>

class Entity : public GameObject
{
public:
	Entity();
	Entity(Sprite* sprite);
	Entity(Sprite* sprite, std::pair<int, int> spawnLocation);
	~Entity();
	Sprite* m_Sprite;
	int GetHp() const;
	int GetAttackDamage() const;
	bool GetAliveStatus() const;
	void reduceHp(int);
protected:
	int Hp;
	int AttackDamage;
	bool isAlive;
};
