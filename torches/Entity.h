#pragma once
#include <map>
#include "Sprite.h"

class Entity
{
public:
	Entity();
	~Entity();
	std::pair<int, int> GetPosition() const;
	void Translate(int x, int y);
	void SetPosition(int x, int y);	
private:
	Sprite* m_Sprite;
	std::pair<int, int> m_Position;
};

