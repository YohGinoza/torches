#include "Sound.h"

SoundManager* SoundManager::_instance;

SoundManager::SoundManager()
{
	if (_instance == nullptr) {
		_instance = new SoundManager();
	}
	else {
		delete _instance;
		return;
	}
}

SoundManager::~SoundManager()
{

}


void SoundManager::playSound(LPCSTR sound)
{
	if (!sound)
		return;
	PlaySound(sound, NULL,  SND_FILENAME| SND_ASYNC); //playsound
}

void SoundManager::playLoop(LPCSTR sound)
{
	if (!sound)
		return;
	PlaySound(sound, NULL, SND_LOOP | SND_ASYNC); //playsound
}

void SoundManager::stopAllSound()
{
	PlaySound(NULL, 0, 0);
}

SoundManager* SoundManager::GetInstance() {
	return _instance;
}