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
	Screen* screen = new Screen(100,75);
	Renderer r();
	Sprite* s = new Sprite("s1", "BitMapSprites/sprite_u1.txt");
	std::cout << s->m_Dimension.first << " " << s->m_Dimension.second << std::endl;
	Entity* e = new Entity(s, std::make_pair(0, 0));
	system("pause");	
	system("cls");
	std::cout << "====\n";
	//Renderer::GetInstance()->Draw(*screen,e);
	Renderer::GetInstance()->Draw(*screen, std::make_pair(0, 0), s);
	system("pause");
	//Game::Init();

	//Game::Loop();

	//Game::Destroy();
	
	system("pause");
	delete s;
	delete screen;
	return 0;
}