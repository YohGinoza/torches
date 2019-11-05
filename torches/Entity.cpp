#include "Entity.h"
#include "EntityManager.h"


Entity::Entity()
{
	this->m_Sprite = nullptr;
	this->m_Position = std::make_pair(0, 0);
}

Entity::Entity(Sprite* sprite) {
	this->m_Sprite = sprite;
	this->m_Position = std::make_pair(0, 0);
}

Entity::Entity(Sprite* sprite, std::pair<int, int> spawnLocation) {
	this->m_Sprite = sprite;
	this->m_Position = spawnLocation;
}

Entity::~Entity()
{
}

std::pair<int,int> Entity::GetPosition() const{
	return this->m_Position;
}

void Entity::Translate(int x, int y) {
	this->m_Position.first += x;
	this->m_Position.second += y;
}

void Entity::SetPosition(int x, int y) {
	this->m_Position.first = x;
	this->m_Position.second = y;
}