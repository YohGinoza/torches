#pragma once

#include "InputBuffer.h"
#include "InputReader.h"
#include "InputWriter.h"


namespace Game 
{
	enum GameState {
		PHASE_MAZE = 0,
		PHASE_COMBAT,
		QUIT
	};

	void Init();

	void Update();

	void Loop();

	void Destroy();

	void setState(int state);
	int getState();

	void debug_input();

	InputBuffer* getInput();
}
