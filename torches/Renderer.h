#pragma once

#include <string>
#include "Screen.h"
#include "Entity.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	static Renderer* GetInstance();
	void Draw(Screen& screen, Entity* entity);
	void Draw(Screen& screen, std::pair<int,int> position, Sprite* sprite);
	void ShowOutput(Screen& screen);
private:
	static Renderer* s_Instance;	
};

