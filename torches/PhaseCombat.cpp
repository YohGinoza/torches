#include "PhaseCombat.h"

PhaseCombat* PhaseCombat::s_Instance = 0;

PhaseCombat::PhaseCombat()
{

}

PhaseCombat::PhaseCombat(Monster<char>* enemy)
{

}

PhaseCombat::~PhaseCombat()
{

}

void PhaseCombat::OnUpdate(float dt)
{
	//generate sequence
	enemy->m_SequenceKeeper;
	//cout sequence
	//getInput
	//compare
	//calculate damage
}

PhaseCombat* PhaseCombat::GetInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new PhaseCombat();
	}
	return s_Instance;
}

void PhaseCombat::DrawSequence(Screen& screen) // draws monster's sequence on screen
{
	screen.ClearScreen();
	
}

