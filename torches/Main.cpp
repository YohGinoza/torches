#include <stdio.h>
#include <windows.h>   // WinApi header
#include <iostream>
#include <string>
#include <time.h>
#include "Entity.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Screen.h"

#include "Game.h"

int main()
{
	Game::Init();

	Game::Loop();

	Game::Destroy();
	
	system("pause");
	return 0;
}