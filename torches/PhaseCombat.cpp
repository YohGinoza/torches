#include "PhaseCombat.h"

PhaseCombat* PhaseCombat::s_Instance = 0;

PhaseCombat::PhaseCombat()
{
	c_enemy = new BeastAlpha();
	c_enemy->GenerateSequence();

	index = 0;
}

PhaseCombat::PhaseCombat(Monster* enemy)
{
	this->c_enemy = enemy;

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
			std::cout << "Damage" << std::endl;

			//remove that key from buffer
			if (index < c_enemy->m_SequenceKeeper.GetRange() - 1) 
			{
				index++;
			}
		}
		else
		{
			//if incorrect
			//calculate damage
			Player::GetInstance()->reduceHp(c_enemy->GetAttackDamage());
			std::cout << "hhhhhhhhhhhhh" << std::endl;
		}
	}

	//if time run out or finish the enemy sequence
	// if() //run out of time
	//{
		/*if (c_enemy->m_SequenceKeeper.GetSequence().size() != 0)
		{
			//calculate remaining sequence damage
		}*/
		//Game::setState(Game::GameState::PHASE_MAZE());
		//delete c_enemy;
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

void PhaseCombat::setMonster(Monster* enemy)
{
	c_enemy = enemy;
}

