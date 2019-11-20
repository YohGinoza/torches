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
	time_req = clock();
	deltaTime = time_req - oldTime;
	oldTime = time_req;
}

Time::~Time()
{

}

float Time::GetDeltaTime() {
	return this->deltaTime;
}
