#include "PhaseCombat.h"
#include "Game.h"
#include "BeastNu.h"
#include "Player.h"

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
	if (Game::getInput()->getKey(c_enemy->m_SequenceKeeper.GetSequence().front))
	{
		//if correct continue
			//calculate damage
		
			//remove that key from buffer
		c_enemy->m_SequenceKeeper.GetSequence().pop();
		std::cout << "Damage" << std::endl;
	}
	else
	{
		//if incorrect stop
		//calculate damage

		//delete c_enemy;
		//Game::setState(Game::GameState::PHASE_MAZE());
	}

	//if time run out or finish the enemy sequence
	// if() //run out of time
	//{
		if (c_enemy->m_SequenceKeeper.GetSequence().size() != 0)
		{
			//calculate remaining sequence damage
		}
		//Game::setState(Game::GameState::PHASE_MAZE());
		delete c_enemy;
	//}
		//delete enemy

		//go back 



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

