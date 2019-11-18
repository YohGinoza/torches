//#include "Time.h"
//
//Time* Time::s_Instance = nullptr;
//
//Time::Time()
//{
//	deltaTime = 0.0f;
//	oldTime = 0.0f;
//
//	if (s_Instance == nullptr) {
//		s_Instance = new Time();
//	}
//	else {
//		delete this;
//		return;
//	}
//
//}
//
//Time* Time::GetInstance() {
//	return s_Instance;
//}
//
//void Time::OnUpdate() {
//	deltaTime = clock() - oldTime;
//	oldTime = clock();
//}
//
//float Time::GetDeltaTime() {
//	return deltaTime;
//}
//
//Time::~Time()
//{
//}
