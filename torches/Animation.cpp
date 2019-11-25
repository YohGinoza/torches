#include "Animation.h"


Animation::Animation()
{
	this->m_FrameCounter = 0;
	this->m_IsEnded = false;
	this->m_UpdatingFrames = 10;
}

Animation::~Animation()
{
}

void Animation::Play(Screen& screen) {	
	if (this->m_FrameCounter < screen.GetScreenWidth() && !m_IsEnded) {
		for (int i = 0; i < screen.GetScreenHeight(); i++) {
			for (int j = 0; j < this->m_FrameCounter; j++) {
				screen.SetData(i, j, '#');
			}
		}
		m_FrameCounter += m_UpdatingFrames;
	}
	else {
		this->m_IsEnded = true;
	}
}

bool Animation::IsEnded()const {
	return this->m_IsEnded;
}

void Animation::SetAnimationSpeed(int speed) {
	this->m_UpdatingFrames = speed;
}