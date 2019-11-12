#include "Game.h"

#include <vector>
#include <iostream>

namespace Game 
{
	void(*gameUpdate)();

	InputReader reader;
	std::thread readerThread;
	InputBuffer* input;

	int state;
	int* CurrentState;
	int* NextState;

	void test_MazeUpdate() 
	{
		std::cout << "maze_phase\n";

		if (input->getKey(KeyCode::KEY_N)) 
		{
			setState(GameState::PHASE_COMBAT);
		}

		if (input->getKey(KeyCode::KEY_ESC))
		{
			setState(GameState::QUIT);
		}
	};

	void test_CombatUpdate() 
	{
		std::cout << "combat_phase\n";

		if (input->getKey(KeyCode::KEY_N))
		{
			setState(GameState::PHASE_MAZE);
		}

		if (input->getKey(KeyCode::KEY_ESC))
		{
			setState(GameState::QUIT);
		}
	};

	void Init() 
	{
		CurrentState = new int;
		NextState = new int;

		*CurrentState = GameState::PHASE_MAZE;
		*NextState = GameState::PHASE_MAZE;

		gameUpdate = test_MazeUpdate;

		input = InputBuffer::instance();
		readerThread = std::thread(reader);
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
					gameUpdate = test_MazeUpdate;

					//gameUpdate = Maze.gameUpdate();
				}
				else if (*NextState == GameState::PHASE_COMBAT)
				{
					*CurrentState = GameState::PHASE_COMBAT;
					gameUpdate = test_CombatUpdate;

					//gameUpdate = Combat.gameUpdate();
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

		gameUpdate();

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
	}

}