#pragma once
#include <map>
#include "Sprite.h"

class Entity
{
public:
	Entity();
	Entity(Sprite* sprite);
	Entity(Sprite* sprite, std::pair<int, int> spawnLocation);
	~Entity();
	std::pair<int, int> GetPosition() const;
	Sprite* m_Sprite;
	void Translate(int x, int y);
	void SetPosition(int x, int y);	
private:	
	std::pair<int, int> m_Position;
};

