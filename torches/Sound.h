#pragma once
#include <iostream>
#include <windows.h>
#include <mmsystem.h>

class SoundManager {
private:
	static SoundManager* _instance;
public:
	SoundManager();
	~SoundManager();
	void playSound(LPCSTR);
	void stopAllSound();
	static SoundManager* GetInstance();
};