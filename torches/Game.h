#pragma once

#include "InputBuffer.h"
#include "InputReader.h"
#include "InputWriter.h"
#include "Screen.h"


namespace Game 
{
	enum GameState {
		PHASE_MAZE = 0,
		PHASE_COMBAT,
		QUIT
	};

	enum Exit {
		EXIT_DIE = 0,
		EXIT_WIN,
	};

	void Init();

	void Update();
	
	void Loop();

	void Exit();

	void Destroy();

	void setState(int state);
	int getState();

	void debug_input();

	void setExit(int exit);

	InputBuffer* getInput();
}
