#include "PhaseCombat.h"
#include "Game.h"
#include "BeastNu.h"

PhaseCombat* PhaseCombat::s_Instance = 0;

PhaseCombat::PhaseCombat()
{
	c_enemy = new BeastNu();
}

PhaseCombat::PhaseCombat(Monster* enemy)
{
	this->c_enemy = enemy;
}


PhaseCombat::~PhaseCombat()
{
}

void PhaseCombat::OnUpdate(float dt)
{
	//get input
	if (Game::getInput()->getKey(KeyCode::KEY_0))
	{
		//if correct continue
			//calculate damage
			//remove that key from buffer
		std::cout << "Damage" << std::endl;
	}
	else
	{
		//if incorrect stop
			//calculate damage
		//std::cout << "hhhhhhhhhhhhh";
		//delete c_enemy;
		//Game::setState(Game::GameState::PHASE_MAZE());
	}

		//delete enemy

		//go back 


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

