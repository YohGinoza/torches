#include "Animation.h"


Animation::Animation()
{
	this->frameCounter = 0;
	this->m_IsEnded = false;
}

Animation::~Animation()
{
}

void Animation::Play(Screen& screen) {	
	if (this->frameCounter < screen.GetScreenWidth() && !m_IsEnded) {
		for (int i = 0; i < screen.GetScreenHeight(); i++) {
			for (int j = 0; j < this->frameCounter; j++) {
				screen.SetData(i, j, '#');
			}
		}
		frameCounter++;
	}
	else {
		this->m_IsEnded = true;
	}
}

bool Animation::IsEnded()const {
	return this->m_IsEnded;
}