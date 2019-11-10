#pragma once

#include <map>

class GameObject
{
public:
	GameObject();
	~GameObject();
	std::pair<int, int> GetPosition() const;
	void Translate(int x, int y);
	void SetPosition(int x, int y);
protected:
	std::pair<int, int> m_Position;
};

