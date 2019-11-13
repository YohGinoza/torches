#include "PhaseCombat.h"
#include "Game.h"

PhaseCombat* PhaseCombat::s_Instance = 0;

PhaseCombat::PhaseCombat()
{

}

PhaseCombat::PhaseCombat(Monster* enemy)
{

}


PhaseCombat::~PhaseCombat()
{
}

void PhaseCombat::OnUpdate(float dt)
{
	//get input
	if (Game::getInput()->getKey(0) != NULL)
	{
		//if correct continue
		if (c_enemy->m_SequenceKeeper.GetSequence()[0] == Game::getInput()->getKey(0))
		{
			std::cout << "Damage" << std::endl;
		}
	}
	//if incorrect stop
	//calculate the damage
}

PhaseCombat* PhaseCombat::GetInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new PhaseCombat();
	}
	return s_Instance;
}

PhaseCombat* PhaseCombat::GetInstance(Monster* enemy)
{
	if (s_Instance == 0)
	{
		s_Instance = new PhaseCombat(enemy);
	}
	return s_Instance;
}

void PhaseCombat::DrawSequence(Screen& screen) // draws monster's sequence on screen
{

}

