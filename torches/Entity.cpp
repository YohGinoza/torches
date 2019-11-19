#include "Entity.h"

Entity::Entity()
{
	this->m_Sprite = nullptr;
	this->m_Position = std::make_pair(0, 0);
}

Entity::~Entity()
{
}

Entity::Entity(Sprite* sprite) {
	this->m_Sprite = sprite;
	this->m_Position = std::make_pair(0, 0);
}

Entity::Entity(Sprite* sprite, std::pair<int, int> spawnLocation) {
	this->m_Sprite = sprite;
	this->m_Position = spawnLocation;
}

int Entity::GetHp() const {
	return Hp;
}

int Entity::GetAttackDamage() const {
	return AttackDamage;
}

bool Entity::GetAliveStatus() const {
	return isAlive;
}

void Entity::reduceHp(int damage)
{
	this->Hp -= damage;
	if (Hp < 0)
	{
		Hp = 0;
	}
}