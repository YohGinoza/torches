#pragma once

#include "InputBuffer.h"
#include "InputReader.h"
#include "InputWriter.h"

namespace Game 
{

	void Init();

	void Update();

	void Loop();

	void Destroy();

	InputBuffer* getInput();
}
