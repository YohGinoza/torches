#include "Game.h"

#include <vector>
#include <iostream>

#include "Phase.h"
#include "PhaseMaze.h"
#include "PhaseCombat.h"

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

	float dt;

	void MazeUpdate(float dt) 
	{
		Maze->OnUpdate(dt);
	}

	void CombatUpdate(float dt) 
	{
		Combat->OnUpdate(dt);
	}

	void Init() 
	{
		CurrentState = new int;
		NextState = new int;

		*CurrentState = GameState::PHASE_COMBAT;
		*NextState = GameState::PHASE_COMBAT;

		gameUpdate = CombatUpdate;

		input = InputBuffer::instance();
		readerThread = std::thread(reader);

		Maze = PhaseMaze::GetInstance();
		Combat = PhaseCombat::GetInstance();

		//pls change this when we have dt
		dt = 0;
	}

	void Loop()
	{
		while (*CurrentState != GameState::QUIT)
		{
			if (*NextState != *CurrentState)
			{
				if (*NextState == GameState::PHASE_MAZE)
				{
					*CurrentState = GameState::PHASE_MAZE;

					gameUpdate = MazeUpdate;
				}
				else if (*NextState == GameState::PHASE_COMBAT)
				{
					*CurrentState = GameState::PHASE_COMBAT;
					gameUpdate = CombatUpdate;
				}
				else if (*NextState == GameState::QUIT)
				{
					*CurrentState = GameState::QUIT;

					break;
				}
			}

			//UpdateLoop
			Update();
		}
	}

	void Update() 
	{
		input->updateInput();

		//gameUpdate(dt);

		debug_input();

		input->clearArray();
	}

	void Destroy() 
	{
		if (readerThread.joinable()) {
			readerThread.join();
		}

		InputBuffer::instance()->destroy();
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