#pragma once
#include "Entity.h"
class Player :
	public Entity
{
public:
	Player();
	~Player();
	static Player* GetInstance();
	void Heal(int value);
private:
	static Player* s_Instance;
};

