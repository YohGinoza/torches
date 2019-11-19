#pragma once
#include <time.h>

class Time
{
	private:
		float deltaTime = 0.0f;
		float oldTime = 0.0f;
		clock_t time_req = clock();
		static Time* s_Instance;
		float test = 0;
	public:
		Time();
		void OnUpdate();
		float GetDeltaTime();
		static Time* GetInstance();
		~Time();
};

