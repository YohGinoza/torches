#pragma once
#include <chrono>

class Time
{
	protected:
		float deltaTime;
		float currTime;
		float oldTime;
		static Time* s_Instance;
	public:
		Time();
		void OnUpdate();
		float GetDeltaTime();
		std::chrono::high_resolution_clock timer;
		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		std::chrono::time_point<std::chrono::high_resolution_clock> end;
		static Time* GetInstance();
		~Time();
};

