#include <stdio.h>
#include <windows.h>   // WinApi header
#include <iostream>
#include <string>
#include <time.h>
#include "Entity.h"
#include "Renderer.h"
#include "Sprite.h"

#include "Game.h"

int main()
{	
	srand(time(NULL));
	
	Game::Init();
	
	Game::Title();

	Game::Loop();
	
	Game::Exit();

	Game::Credit();
	
	Game::Destroy();
	
	system("pause");
	
	return 0;
}