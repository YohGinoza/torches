#include "Time.h"
#include <iostream>

Time* Time::s_Instance = nullptr;

Time::Time()
{
	deltaTime = 0;
	oldTime = 0;
	currTime = 0;
}

Time* Time::GetInstance() {
	if (s_Instance == nullptr) {
		s_Instance = new Time();
	}
	return s_Instance;
}

void Time::OnUpdate() {
	using s = std::chrono::duration<float, std::ratio<1, 1>>;
	oldTime = currTime;
	currTime = std::chrono::duration_cast<s>(end - start).count();
	deltaTime = currTime - oldTime;
}

Time::~Time()
{

}

float Time::GetDeltaTime() {
	return this->deltaTime;
}
