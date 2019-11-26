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
#include "Sound.h"

class PhaseMaze;
class GameUpdater;

#define MAIN_SCREEN_WIDTH 230
#define MAIN_SCREEN_HEIGHT 90
#define SPRITES_PER_TYPE 4

namespace Game 
{
	typedef void(*GameUpdate)(float);
	GameUpdate gameUpdate;

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

	Screen* MainScreen = new Screen(MAIN_SCREEN_WIDTH, MAIN_SCREEN_HEIGHT);
	Screen* MiniMapScreen = new Screen(MAP_WIDTH * FIXED_OFFSET, MAP_WIDTH * FIXED_OFFSET);
	Screen* MazeScreen = new Screen(ROOM_WIDTH, ROOM_HEIGHT);
	Screen* BattleScreen = new Screen(10 * SPRITE_SPECIAL_OFFSET, MAIN_SCREEN_HEIGHT - 30);

	int randType = 0;

	Animation* BattleIntro = new Animation();

	bool playAnimation = false;

	Time t;

	void DrawHpBar(Screen& screen) {		
		int MaxHeight = 3;
		int playerHP = Player::GetInstance()->GetHp();

		int WidthOffset = SpriteManager::GetInstance()->GetSprite("hpBar")->m_Dimension.first;
		int HeightOffset = screen.GetScreenHeight() - SpriteManager::GetInstance()->GetSprite("hpBar")->m_Dimension.second;

		Renderer::GetInstance()->Draw(screen, std::make_pair(0, HeightOffset), SpriteManager::GetInstance()->GetSprite("hpBar"));
		
		
		for (int i = HeightOffset + 4; i > HeightOffset + 1; i--)
		{
			for (int j = WidthOffset; j < WidthOffset + (playerHP); j++)
			{
				if (j < screen.GetScreenWidth())
				{
					screen.SetData(i, j,'=');
				}
			}
		}
	}

	void MazeUpdate(float dt)
	{
		Maze->OnUpdate(dt, *MazeScreen);
	}

	class MazeUpdater
	{
	public:
		GameUpdate GetUpdate()
		{
			return MazeUpdate;
		}
	};

	void CombatUpdate(float dt)
	{
		Combat->OnUpdate(Time::GetInstance()->GetDeltaTime(), *BattleScreen);
	}

	class CombatUpdater
	{
	public:
		GameUpdate GetUpdate()
		{
			return CombatUpdate;
		}
	};

	void AnimationUpdate(float dt) {
		if (!BattleIntro->IsEnded() && playAnimation) {
			BattleIntro->Play(*MainScreen);			
		}
		if (BattleIntro->IsEnded()) {
			Game::setState(Game::PHASE_COMBAT);
			playAnimation = false;
			BattleIntro->ResetAnimation();
		}
	}

	class AnimationUpdater {
	public:
		GameUpdate GetUpdate()
		{
			return AnimationUpdate;
		}
	};

	template <class UpdatePolicy>
	class GameUpdater : public UpdatePolicy
	{ };

	void Init() 
	{

		Renderer r();
		SpriteManager sm();

		BattleIntro->SetAnimationSpeed(50);
		
		SpriteManager::GetInstance()->PushBack(new Sprite("BeastMix", "BitMapSprites/BeastM.txt"));
		SpriteManager::GetInstance()->PushBack(new Sprite("youDied", "BitMapSprites/YouDied.txt"));
		SpriteManager::GetInstance()->PushBack(new Sprite("youWin", "BitMapSprites/YouWin.txt"));
		SpriteManager::GetInstance()->PushBack(new Sprite("credit", "BitMapSprites/credit.txt", 1));
		SpriteManager::GetInstance()->PushBack(new Sprite("hpBar", "BitMapSprites/hp.txt"));
		SpriteManager::GetInstance()->LoadInputSprites();
		
		// load beast alpha sprites
		std::string beastType = "BeastAlpha_";
		std::string dir = "BitMapSprites/";
		for (int i = 0; i < SPRITES_PER_TYPE; i++) {
			std::string name = beastType;
			name += std::to_string(i);
			std::string path = dir;
			path += name;
			path += ".txt";
			SpriteManager::GetInstance()->PushBack(new Sprite(name, path));
		}

		// load beast number sprites
		beastType = "BeastNu_";
		for (int i = 0; i < SPRITES_PER_TYPE; i++) {
			std::string name = beastType;
			name += std::to_string(i);
			std::string path = dir;
			path += name;
			path += ".txt";
			SpriteManager::GetInstance()->PushBack(new Sprite(name, path));
		}		

		CurrentState = new int;
		NextState = new int;
		Exit_condition = new int;
		
		*CurrentState = GameState::PHASE_MAZE;
		*NextState = GameState::PHASE_MAZE;		

		GameUpdater<MazeUpdater> mazeUpdate;
		gameUpdate = mazeUpdate.GetUpdate();

		input = InputBuffer::instance();
		readerThread = std::thread(reader);


		Maze = PhaseMaze::GetInstance();
		Combat = PhaseCombat::GetInstance();

		dt = Time::GetInstance()->GetDeltaTime();
	}

	void Title() 
	{
		SoundManager::GetInstance()->playLoop("Sound/Main_Screen.wav");
		Sprite* bg = new Sprite("bg", "BitMapSprites/titleScreen.txt", 1);
		Sprite* bg_t = new Sprite("bg_torches", "BitMapSprites/title_torches.txt", 1);
		SpriteAnimation* f = new SpriteAnimation("flame", "BitMapSprites/flame.txt", 4, 3);

		while (1) {

			input->updateInput();
			system("cls");
			MainScreen->ClearScreen();
			Renderer::GetInstance()->DrawFull(*MainScreen, std::make_pair((MainScreen->GetScreenWidth()*0.5) - (bg->m_Dimension.first*0.5), 0), bg);
			Renderer::GetInstance()->DrawFull(*MainScreen, std::make_pair((MainScreen->GetScreenWidth()*0.5) - (bg_t->m_Dimension.first*0.5), 40), bg_t);
			Renderer::GetInstance()->DrawAnimation(*MainScreen, std::make_pair(0, 40), f);
			Renderer::GetInstance()->DrawAnimation(*MainScreen, std::make_pair(MainScreen->GetScreenWidth() - f->GetWidthPerFrame(), 40), f);
			Renderer::GetInstance()->ShowOutput(*MainScreen);
			if (input->KeyPress()) {				
				break;
			}
			input->clearArray();
		}

		SoundManager::GetInstance()->playLoop("Sound/maze.wav");
		MainScreen->ClearScreen();

		delete f;
		delete bg;
		delete bg_t;
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
					SoundManager::GetInstance()->playLoop("Sound/maze.wav");
					GameUpdater<MazeUpdater> mazeUpdate;
					gameUpdate = mazeUpdate.GetUpdate();

					MainScreen->ClearScreen();
					MazeScreen->ClearScreen();
					BattleScreen->ClearScreen();
					MiniMapScreen->ClearScreen();

					system("cls");
					MazeScreen->ClearScreen();
					PhaseMaze::GetInstance()->DrawMaze(*MazeScreen);					
					MainScreen->CombineScreen(*MazeScreen, std::make_pair(0, 0));					
					PhaseMaze::GetInstance()->DrawMinimap(*MiniMapScreen);
					MainScreen->CombineScreen(*MiniMapScreen, std::make_pair(0, MazeScreen->GetScreenHeight() + FIXED_OFFSET));
					DrawHpBar(*MainScreen);
					Renderer::GetInstance()->ShowOutput(*MainScreen);
				}
				else if (*NextState == GameState::PHASE_ANIMATION)
				{
					playAnimation = true;
					randType = rand() % 3;					
					*CurrentState = GameState::PHASE_ANIMATION;

					MainScreen->ClearScreen();
					MazeScreen->ClearScreen();
					BattleScreen->ClearScreen();
										
					GameUpdater<AnimationUpdater> animationUpdate;
					gameUpdate = animationUpdate.GetUpdate();					
				}
				else if (*NextState == GameState::PHASE_COMBAT)
				{
					PhaseCombat::GetInstance()->InitCombat(randType, dt);
					*CurrentState = GameState::PHASE_COMBAT;
					SoundManager::GetInstance()->playLoop("Sound/battle.wav");

					MainScreen->ClearScreen();
					MazeScreen->ClearScreen();
					BattleScreen->ClearScreen();
					MiniMapScreen->ClearScreen();

					system("cls");					
					MazeScreen->ClearScreen();
					PhaseCombat::GetInstance()->DrawCombatPhase(*BattleScreen);
					MainScreen->CombineScreen(*BattleScreen, std::make_pair(MiniMapScreen->GetScreenWidth(), 0));
					PhaseMaze::GetInstance()->DrawMaze(*MazeScreen);
					MainScreen->CombineScreen(*MazeScreen, std::make_pair(0, 0));
					PhaseMaze::GetInstance()->DrawMinimap(*MiniMapScreen);
					MainScreen->CombineScreen(*MiniMapScreen, std::make_pair(0, MazeScreen->GetScreenHeight() + FIXED_OFFSET));
					DrawHpBar(*MainScreen);
					Renderer::GetInstance()->ShowOutput(*MainScreen);
					
					GameUpdater<CombatUpdater> combatUpdate;
					gameUpdate = combatUpdate.GetUpdate();					
				}
				else if (*NextState == GameState::QUIT)
				{
					MainScreen->ClearScreen();
					MazeScreen->ClearScreen();
					BattleScreen->ClearScreen();

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
		
		gameUpdate(Time::GetInstance()->GetDeltaTime());	
		
		if (*CurrentState == PHASE_COMBAT)
		{
			if (input->KeyPress()) {
				system("cls");
				MainScreen->ClearScreen();
				MazeScreen->ClearScreen();
				PhaseCombat::GetInstance()->DrawCombatPhase(*BattleScreen);				
				MainScreen->CombineScreen(*BattleScreen, std::make_pair(MiniMapScreen->GetScreenWidth(), 0));
				PhaseMaze::GetInstance()->DrawMaze(*MazeScreen);
				MainScreen->CombineScreen(*MazeScreen, std::make_pair(0, 0));
				PhaseMaze::GetInstance()->DrawMinimap(*MiniMapScreen);
				MainScreen->CombineScreen(*MiniMapScreen, std::make_pair(0, MazeScreen->GetScreenHeight() + FIXED_OFFSET));
				DrawHpBar(*MainScreen);
				Renderer::GetInstance()->ShowOutput(*MainScreen);				
			}
		}
		else if (*CurrentState == PHASE_ANIMATION) {
			system("cls");
			Renderer::GetInstance()->ShowOutput(*MainScreen);
		}
		else if (*CurrentState == PHASE_MAZE) {			
			PhaseMaze::GetInstance()->UpdateDetectRange();
			if (input->KeyPress()) {
				MainScreen->ClearScreen();
				system("cls");
				MainScreen->ClearScreen();
				MazeScreen->ClearScreen();
				PhaseMaze::GetInstance()->DrawMaze(*MazeScreen);
				MainScreen->CombineScreen(*MazeScreen, std::make_pair(0, 0));
				MiniMapScreen->ClearScreen();				
				PhaseMaze::GetInstance()->DrawMinimap(*MiniMapScreen);
				MainScreen->CombineScreen(*MiniMapScreen, std::make_pair(0, MazeScreen->GetScreenHeight() + FIXED_OFFSET));
				DrawHpBar(*MainScreen);
				Renderer::GetInstance()->ShowOutput(*MainScreen);					
			}						
		}	
		
		
		input->clearArray();
	}

	void Exit() {
		system("cls");

		if (*Exit_condition == EXIT_WIN) 
		{
			MainScreen->ClearScreen();
			int midscreenposX = -(SpriteManager::GetInstance()->GetSprite("youWin")->m_Dimension.first*0.5) + (MainScreen->GetScreenWidth()*0.5);
			int midscreenposY = -(SpriteManager::GetInstance()->GetSprite("youWin")->m_Dimension.second*0.5) + (MainScreen->GetScreenHeight()*0.5);
			SoundManager::GetInstance()->playSound("Sound/youWin.wav");

			Renderer::GetInstance()->Draw(*MainScreen, std::make_pair(midscreenposX, midscreenposY), SpriteManager::GetInstance()->GetSprite("youWin"));
			Renderer::GetInstance()->ShowOutput(*MainScreen);
		}
		else if (*Exit_condition == EXIT_DIE) 
		{
			MainScreen->ClearScreen();
			int midscreenposX = -(SpriteManager::GetInstance()->GetSprite("youDied")->m_Dimension.first*0.5) + (MainScreen->GetScreenWidth()*0.5);
			int midscreenposY = -(SpriteManager::GetInstance()->GetSprite("youDied")->m_Dimension.second*0.5) + (MainScreen->GetScreenHeight()*0.5);
			SoundManager::GetInstance()->playSound("Sound/youDied.wav");

			Renderer::GetInstance()->Draw(*MainScreen, std::make_pair(midscreenposX, midscreenposY), SpriteManager::GetInstance()->GetSprite("youDied"));
			Renderer::GetInstance()->ShowOutput(*MainScreen);
		}
		system("pause");
	}

	void Credit() {	
		SoundManager::GetInstance()->stopAllSound();
		system("cls");
		bool exit = false;
		int heightOffset = MainScreen->GetScreenHeight() + 1;
		int widthOffset = (MainScreen->GetScreenWidth()*0.5) - (SpriteManager::GetInstance()->GetSprite("credit")->m_Dimension.first*0.5);
		MainScreen->ClearScreen();
		std::pair<int, int> pos = std::make_pair(widthOffset, heightOffset);
		Sprite* creditRoll = SpriteManager::GetInstance()->GetSprite("credit");
		float timer = 0;
		float tick = 0.1f;
		Time::GetInstance()->start = Time::GetInstance()->timer.now();		
		bool startPlayingBGM = false;
		while (1) {
			timer += Time::GetInstance()->GetDeltaTime();
			if (timer < 0) {
				timer = 0;
			}
			if (timer >= tick) {					
				timer = 0;	// reset timer
				pos.second -= 1;	// move up
				system("cls");
				MainScreen->ClearScreen();
				Renderer::GetInstance()->DrawFull(*MainScreen, pos, creditRoll);
				Renderer::GetInstance()->ShowOutput(*MainScreen);
				if (pos.second <= -(creditRoll->m_Dimension.second) - 5) {
					break;
				}
				if (!startPlayingBGM) {
					SoundManager::GetInstance()->playSound("Sound/endCredits.wav");
					startPlayingBGM = true;
				}
			}			
			Time::GetInstance()->end = Time::GetInstance()->timer.now();
			Time::GetInstance()->OnUpdate();
		}
	}

	void Destroy() 
	{
		if (readerThread.joinable()) {
			readerThread.join();
		}

		InputBuffer::instance()->destroy();
		delete BattleIntro;
		delete MainScreen;
		delete MazeScreen;
		delete MiniMapScreen;		
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