#pragma once
#include <time.h>

class Time
{
private:
	float deltaTime;
	float oldTime;
	clock_t time_req;
	static Time* s_Instance;
public:
	Time();
	void OnUpdate();
	float GetDeltaTime();
	static Time* GetInstance();
	~Time();
};

