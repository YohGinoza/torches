#include "PhaseCombat.h"

PhaseCombat* PhaseCombat::s_Instance = 0;

PhaseCombat::PhaseCombat()
{
	index = 0;
}

PhaseCombat::~PhaseCombat()
{

}

void PhaseCombat::OnUpdate(float dt)
{
	//get input
	if (Game::getInput()->KeyPress()) {

		if (Game::getInput()->getKey(c_enemy->m_SequenceKeeper.GetSequence(index)))
		{
			//if correct
			//calculate damage
			c_enemy->reduceHp(Player::GetInstance()->GetAttackDamage());
			std::cout << c_enemy->m_SequenceKeeper.GetRange() << ", " << index << std::endl;

			//go to next sequence
			index++;

		}
		else
		{
			//if incorrect
			//calculate damage
			Player::GetInstance()->reduceHp(c_enemy->GetAttackDamage());
		}
	}

	//if time run out or finish the enemy sequence
	if(COMBAT_TIME_LIMIT < startTime - dt) //run out of time
	{
		Player::GetInstance()->reduceHp(c_enemy->GetAttackDamage() * c_enemy->m_SequenceKeeper.GetRange() - (index + 1));
		Game::setState(Game::GameState::PHASE_MAZE());
		delete c_enemy;
		index = 0;
	}

		//delete enemy

		//go back 

	//if finish sequence, go to maze phase
	if (c_enemy->m_SequenceKeeper.GetRange() - 1 < index)
	{
		//calculate remaining sequence damage
		Game::setState(Game::PHASE_MAZE);
		delete c_enemy;
		index = 0;
	}

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
	
}

void PhaseCombat::InitCombat(int e_type, float dt)
{
	if (e_type == BeastType::BeatsNum)
	{
		c_enemy = new BeastNu();
	}
	else
	{
		c_enemy = new BeastAlpha();
	}
	startTime = dt;
}

