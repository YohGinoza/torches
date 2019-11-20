#pragma once

#include "Screen.h"

class Animation
{
public:
	Animation();
	~Animation();
	void Play(Screen& screen);
	bool IsEnded() const;
private:
	bool m_IsEnded;
	int frameCounter;
	int maxFrame;
};
