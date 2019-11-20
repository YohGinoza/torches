#include "Game.h"

#include <vector>
#include <iostream>

#include "Phase.h"
#include "PhaseMaze.h"
#include "PhaseCombat.h"
#include "Game.h"
#include "Time.h"
#include "Renderer.h"
#include "Animation.h"

class PhaseMaze;

namespace Game 
{
	void(*gameUpdate)(float dt);

	InputReader reader;
	std::thread readerThread;
	InputBuffer* input;

	PhaseMaze* Maze;
	PhaseCombat* Combat;

	int state;
	int* CurrentState;
	int* NextState;

	int* Exit_condition;

	float dt = Time::GetInstance()->GetDeltaTime();

	Screen* gameScreen = new Screen(150, 60);
	int randType = 0;
	Animation* animationNu = nullptr;
	Animation* animationAlpha = nullptr;
	bool playAnimation = false;
	bool alpha_anim = false;
	bool num_anim = false;

	Time t;

	void MazeUpdate(float dt) 
	{
		Maze->OnUpdate(dt, *gameScreen);
	}

	void CombatUpdate(float dt) 
	{
		Combat->OnUpdate(Time::GetInstance()->GetDeltaTime(), *gameScreen);
	}

	void AnimationUpdate(float dt) {	
		if (alpha_anim) {
			if (!animationAlpha->IsEnded() && playAnimation) {
				animationAlpha->Play(*gameScreen);
				Renderer::GetInstance()->ShowOutput(*gameScreen);				
			}			
			if (animationAlpha->IsEnded()) {
				Game::setState(Game::PHASE_COMBAT);
				playAnimation = false;
				alpha_anim = false;
			}					
		}
		else if (num_anim) {
			if (!animationNu->IsEnded() && playAnimation) {
				animationNu->Play(*gameScreen);
				Renderer::GetInstance()->ShowOutput(*gameScreen);
			}
			if (animationNu->IsEnded()) {
				Game::setState(Game::PHASE_COMBAT);
				playAnimation = false;
				num_anim = false;
			}
		}
		
	}

	void Init() 
	{

		Renderer r();
		SpriteManager sm();

		SpriteManager::GetInstance()->PushBack(new Sprite("beastAlpha", "BitMapSprites/BeastAlpha.txt"));
		SpriteManager::GetInstance()->PushBack(new Sprite("beastNu", "BitMapSprites/BeastNu.txt"));
		SpriteManager::GetInstance()->PushBack(new Sprite("youDied", "BitMapSprites/YouDied.txt"));
		SpriteManager::GetInstance()->PushBack(new Sprite("youWin", "BitMapSprites/YouWin.txt"));
		SpriteManager::GetInstance()->LoadInputSprites();

		CurrentState = new int;
		NextState = new int;
		Exit_condition = new int;
		
		*CurrentState = GameState::PHASE_MAZE;
		*NextState = GameState::PHASE_MAZE;

		gameUpdate = MazeUpdate;

		input = InputBuffer::instance();
		readerThread = std::thread(reader);


		Maze = PhaseMaze::GetInstance();
		Combat = PhaseCombat::GetInstance();

		//pls change this when we have dt
		dt = Time::GetInstance()->GetDeltaTime();				
		//PhaseCombat::GetInstance()->InitCombat(rand() % 2, dt);
	}

	void Loop()
	{
		Time::GetInstance()->start = Time::GetInstance()->timer.now();
		while (*CurrentState != GameState::QUIT)
		{
			if (*NextState != *CurrentState)
			{
				if (*NextState == GameState::PHASE_MAZE)
				{
					*CurrentState = GameState::PHASE_MAZE;

					gameUpdate = MazeUpdate;
				}
				else if (*NextState == GameState::PHASE_ANIMATION)
				{
					playAnimation = true;
					randType = rand() % 2;
					switch (randType) {
					case 0:
					{
						if (animationNu != nullptr) {
							delete animationNu;
						}
						animationNu = new Animation();
						num_anim = true;
					}
						break;
					case 1: 
					{
						if (animationAlpha != nullptr) {
							delete animationAlpha;
						}
						animationAlpha = new Animation();
						alpha_anim = true;
					}						
						break;
					}
					*CurrentState = GameState::PHASE_ANIMATION;

					gameUpdate = AnimationUpdate;
				}
				else if (*NextState == GameState::PHASE_COMBAT)
				{															
					PhaseCombat::GetInstance()->InitCombat(randType, dt);
					*CurrentState = GameState::PHASE_COMBAT;
					gameUpdate = CombatUpdate;
				}
				else if (*NextState == GameState::QUIT)
				{
					*CurrentState = GameState::QUIT;

					break;
				}
			}
			Time::GetInstance()->end = Time::GetInstance()->timer.now();
			//UpdateLoop
			Time::GetInstance()->OnUpdate();
			Update();

		}
	}

	void Update() 
	{
		input->updateInput();

		gameScreen->ClearScreen();

		gameUpdate(Time::GetInstance()->GetDeltaTime());

		//debug_input();		
		if (*CurrentState == PHASE_COMBAT)
		{
			system("cls");
			std::cout << "PLAYER HP: " << Player::GetInstance()->GetHp() << std::endl;
			Renderer::GetInstance()->ShowOutput(*gameScreen);
		}
		else if (*CurrentState == PHASE_ANIMATION) {

			Renderer::GetInstance()->ShowOutput(*gameScreen);
		}

		input->clearArray();
	}

	void Exit() {
		system("cls");

		if (*Exit_condition == EXIT_WIN) 
		{
			gameScreen->ClearScreen();
			int midscreenposX = -(SpriteManager::GetInstance()->GetSprite("youWin")->m_Dimension.first*0.5) + (gameScreen->GetScreenWidth()*0.5);
			int midscreenposY = -(SpriteManager::GetInstance()->GetSprite("youWin")->m_Dimension.second*0.5) + (gameScreen->GetScreenHeight()*0.5);
			
			Renderer::GetInstance()->Draw(*gameScreen, std::make_pair(midscreenposX, midscreenposY), SpriteManager::GetInstance()->GetSprite("youWin"));
			Renderer::GetInstance()->ShowOutput(*gameScreen);
		}
		else if (*Exit_condition == EXIT_DIE) 
		{
			gameScreen->ClearScreen();
			int midscreenposX = -(SpriteManager::GetInstance()->GetSprite("youDied")->m_Dimension.first*0.5) + (gameScreen->GetScreenWidth()*0.5);
			int midscreenposY = -(SpriteManager::GetInstance()->GetSprite("youDied")->m_Dimension.second*0.5) + (gameScreen->GetScreenHeight()*0.5);

			Renderer::GetInstance()->Draw(*gameScreen, std::make_pair(midscreenposX, midscreenposY), SpriteManager::GetInstance()->GetSprite("youDied"));
			Renderer::GetInstance()->ShowOutput(*gameScreen);
		}
	}

	void Destroy() 
	{
		if (readerThread.joinable()) {
			readerThread.join();
		}

		InputBuffer::instance()->destroy();
		delete animationAlpha;
		delete animationNu;
	}
	
	InputBuffer* getInput() 
	{
		return input;
	}

	int getState() 
	{
		return *CurrentState;
	}

	void setState(int state) 
	{
		*NextState = state;
	}

	void setExit(int exit) {
		*Exit_condition = exit;
	}

	void debug_input() {

		if (input->getKey(KEY_W))
		{
			std::cout << "W\n";
		}

		if (input->getKey(KEY_A))
		{
			std::cout << "A\n";
		}

		if (input->getKey(KEY_S))
		{
			std::cout << "S\n";
		}

		if (input->getKey(KEY_D))
		{
			std::cout << "D\n";
		}

		if (input->getKey(KEY_1))
		{
			std::cout << "1\n";
		}

		if (input->getKey(KEY_LEFT))
		{
			std::cout << "LEFT\n";
		}

		if (input->getKey(KEY_RIGHT))
		{
			std::cout << "RIGHT\n";
		}

		if (input->getKey(KEY_UP))
		{
			std::cout << "UP\n";
		}

		if (input->getKey(KEY_DOWN)) {
			std::cout << "DOWN\n";
		}

		if (input->getKey(KEY_ESC)) {
			std::cout << "ESC\n";
		}

		if (input->KeyPress()) {
			std::cout << "yay\n";
		}
	}

}