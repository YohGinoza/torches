#include "PhaseCombat.h"
#include "Renderer.h"

PhaseCombat* PhaseCombat::s_Instance = 0;

PhaseCombat::PhaseCombat()
{
	c_enemy = new BeastAlpha(10, 5);
	c_enemy->GenerateSequence();

	index = 0;
}

PhaseCombat::~PhaseCombat()
{
	if (this->c_enemy != nullptr) {
		delete c_enemy;
	}
}

void PhaseCombat::OnUpdate(float dt, Screen& screen)
{
	if (Player::GetInstance()->GetHp() <= 0)
	{
		Game::setExit(Game::EXIT_DIE);
		Game::setState(Game::GameState::QUIT);
		return;
	}

	//get input
	if (Game::getInput()->KeyPress()) {

		if (Game::getInput()->getKey(c_enemy->m_SequenceKeeper.GetSequence(index)))
		{
			//if correct
			//calculate damage
			c_enemy->reduceHp(Player::GetInstance()->GetAttackDamage());
			//std::cout << c_enemy->m_SequenceKeeper.GetRange() << ", " << index << std::endl;

			//go to next sequence
			index++;

		}
		else if (!Game::getInput()->getKey(KeyCode::KEY_W) && 
			!Game::getInput()->getKey(KeyCode::KEY_D) && 
			!Game::getInput()->getKey(KeyCode::KEY_A) && 
			!Game::getInput()->getKey(KeyCode::KEY_S))
		{
			//if incorrect
			//calculate damage
			Player::GetInstance()->reduceHp(c_enemy->GetAttackDamage());
		}
	}

	//if time run out or finish the enemy sequence
	timeCounter += dt;
	if(COMBAT_TIME_LIMIT < timeCounter) //run out of time
	{
		Player::GetInstance()->reduceHp(c_enemy->GetAttackDamage() * c_enemy->m_SequenceKeeper.GetRange() - (index + 1));
		Game::setState(Game::PHASE_MAZE);
		if (this->c_enemy != nullptr) {
			delete c_enemy;
		}
	}
	//debug
		//std::cout << "dt: " << dt << "Start: " << timeCounter << std::endl;
	//delete enemy

	//go back 

	//if finish sequence, go to maze phase
	if (c_enemy->m_SequenceKeeper.GetRange() - 1 < index)
	{
		//calculate remaining sequence damage
		Game::setState(Game::PHASE_MAZE);
		this->c_enemy->SetAliveStatus(false);;
	}

	//DrawCombatPhase(screen);	
}

PhaseCombat* PhaseCombat::GetInstance()
{
	if (s_Instance == 0)
	{
		s_Instance = new PhaseCombat();
	}
	return s_Instance;
}

void PhaseCombat::DrawCombatPhase(Screen& screen) // draws monster's sequence on screen
{
	if (this->c_enemy != nullptr && this->c_enemy->GetAliveStatus()) {
		this->c_enemy->SetPosition((-this->c_enemy->m_Sprite->m_Dimension.first*0.5) + (screen.GetScreenWidth()*0.5), (screen.GetScreenHeight()*0.25));
		//Sprite* tmp = SpriteManager::GetInstance()->GetSprite("battle_bg");
		//std::pair<int, int> bgCenter = std::make_pair<int, int>(tmp->m_Dimension.first*0.5, tmp->m_Dimension.second*0.5);
		//Renderer::GetInstance()->DrawFull(screen, std::pair(), SpriteManager::GetInstance()->GetSprite("battle_bg"));
		Renderer::GetInstance()->Draw(screen, this->c_enemy);
		int translateToCenter = -SPRITE_SPECIAL_OFFSET * this->c_enemy->m_SequenceKeeper.GetRange() * 0.5f;
		int firstOffsetX = translateToCenter + (screen.GetScreenWidth() * 0.5f);
		std::pair<int, int> offset(firstOffsetX, screen.GetScreenHeight() - SPRITE_SPECIAL_OFFSET - 1);
		for (int i = 0; i < this->c_enemy->m_SequenceKeeper.GetRange(); i++) {
			std::string spriteName = "sprite_input_" + std::to_string(this->c_enemy->m_SequenceKeeper.GetSequence(i));
			if (i < this->index) {
				Renderer::GetInstance()->DrawReverse(screen, offset, SpriteManager::GetInstance()->GetSprite(spriteName));
			}
			else {
				Renderer::GetInstance()->Draw(screen, offset, SpriteManager::GetInstance()->GetSprite(spriteName));				
			}
			offset.first += SPRITE_SPECIAL_OFFSET;
		}
	}	
}

void PhaseCombat::InitCombat(int e_type, float dt)
{
	timeCounter = 0.0f;
	index = 0;
	int randSpriteNum = rand() % 4;

	if (e_type == BeastType::BeastNum)
	{
		c_enemy = new BeastNu();
		c_enemy->GenerateSequence();
		c_enemy->m_Sprite = SpriteManager::GetInstance()->GetSprite("BeastNu_" + '0');
	}
	else if(e_type == BeastType::BeastAl)
	{
		c_enemy = new BeastAlpha();
		c_enemy->GenerateSequence();
		c_enemy->m_Sprite = SpriteManager::GetInstance()->GetSprite("BeastAlpha_" + '0');
	}
	else if (e_type == BeastType::BeastM)
	{
		c_enemy = new BeastMix(); 
		c_enemy->GenerateSequence();
		c_enemy->m_Sprite = SpriteManager::GetInstance()->GetSprite("BeastMix");
	}
}

