#include "Time.h"
#include <iostream>

Time* Time::s_Instance = nullptr;

Time::Time()
{
	
}

Time* Time::GetInstance() {
	if (s_Instance == nullptr) {
		s_Instance = new Time();
	}
	return s_Instance;
}

void Time::OnUpdate() {
	using ms = std::chrono::duration<float, std::milli>;
	deltaTime = std::chrono::duration_cast<ms>(end - start).count();
}

Time::~Time()
{

}

float Time::GetDeltaTime() {
	return this->deltaTime;
}
