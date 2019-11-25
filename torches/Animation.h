#pragma once

#include "Screen.h"

class Animation
{
public:
	Animation();
	~Animation();
	void Play(Screen& screen);
	bool IsEnded() const;
	void SetAnimationSpeed(int speed);
private:
	bool m_IsEnded;
	int m_FrameCounter;
	int m_UpdatingFrames;
};
