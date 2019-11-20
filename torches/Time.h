#pragma once
#include <chrono>

class Time
{
	private:
		float deltaTime;
		std::chrono::high_resolution_clock timer;
		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		std::chrono::time_point<std::chrono::high_resolution_clock> end;
		static Time* s_Instance;
	public:
		Time();
		void OnUpdate();
		float GetDeltaTime();
		static Time* GetInstance();
		~Time();
};

