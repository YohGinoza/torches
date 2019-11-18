#include "PhaseMaze.h"

PhaseMaze* PhaseMaze::s_Instance = nullptr;

PhaseMaze* PhaseMaze::GetInstance() {
	if (s_Instance == nullptr) {
		s_Instance = new PhaseMaze();
	}

	return s_Instance;
}

PhaseMaze::PhaseMaze()
{

}


PhaseMaze::~PhaseMaze()
{
}

void PhaseMaze::OnUpdate(float dt) 
{
	std::cout << "maze_phase\n";
}
