#include "Time.h"
#include <iostream>

Time* Time::s_Instance = nullptr;

Time::Time()
{
	deltaTime = 0;
}

Time* Time::GetInstance() {
	if (s_Instance == nullptr) {
		s_Instance = new Time();
	}
	return s_Instance;
}

void Time::OnUpdate() {
	using s = std::chrono::duration<float, std::ratio<1, 1>>;
	deltaTime = std::chrono::duration_cast<s>(end - start).count();
}

Time::~Time()
{

}

float Time::GetDeltaTime() {
	return this->deltaTime;
}
