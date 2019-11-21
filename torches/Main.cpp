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
	std::cout << "About to print bg + monster" << std::endl;
	Renderer r();
	Screen* screen = new Screen(150, 60);
	Sprite* bg = new Sprite("bg", "BitMapSprites/bg1.txt",1);
	Sprite* e = new Sprite("enemy", "BitMapSprites/pumpkin.txt");
	Renderer::GetInstance()->DrawFull(*screen, std::make_pair(0, 0), bg);
	int screenCenter = -(e->m_Dimension.first*0.5) + (screen->GetScreenWidth()*0.5);
	Renderer::GetInstance()->Draw(*screen, std::make_pair(screenCenter, 0), e);
	//srand(time(NULL));
	//
	//Game::Init();
	//
	//Game::Loop();
	//
	//Game::Exit();
	//
	//Game::Destroy();
	
	system("pause");
	
	return 0;
}