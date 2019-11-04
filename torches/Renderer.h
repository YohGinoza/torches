#pragma once

#include <string>
#include "Sprite.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	static Renderer* GetInstance();
	void Draw(std::pair<int,int> );
private:
	static Renderer* s_Instance;	
};

