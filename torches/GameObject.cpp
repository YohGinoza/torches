#include "GameObject.h"

/////////////Game Object/////////////////

GameObject::GameObject()
{
	this->m_Position = std::make_pair(0, 0);
}


GameObject::~GameObject()
{
}

std::pair<int, int> GameObject::GetPosition() const {
	return this->m_Position;
}

void GameObject::Translate(int x, int y) {
	this->m_Position.first += x;
	this->m_Position.second += y;
}

void GameObject::SetPosition(int x, int y) {
	this->m_Position.first = x;
	this->m_Position.second = y;
}