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
	Screen* screen = new Screen(150,60);
	Renderer r();
	Sprite* s = new Sprite("s1", "BitMapSprites/sprite_u1.txt");
	Sprite* s2 = new Sprite("s2", "BitMapSprites/BeastAlpha.txt");
	Sprite* s3 = new Sprite("s3", "BitMapSprites/BeastNu.txt");
	Sprite* s4 = new Sprite("s3", "BitMapSprites/phelop.txt");
	Entity* e = new Entity(s, std::make_pair(0, 0));
	Entity* e2 = new Entity(s2, std::make_pair(0, 0));
	Entity* e3 = new Entity(s3, std::make_pair(0, 0));
	Entity* e4 = new Entity(s4, std::make_pair(0, 0));
	system("pause");	
	//system("cls");

	while (1) {		
		char input;
		std::cin >> input;
		system("cls");
		if (input == '4') {
			e2->Translate(-1, 0);
		}
		else if (input == '6') {
			e2->Translate(1, 0);
		}
		else if (input == '2') {
			e2->Translate(0, 1);
		}
		else if (input == '8') {
			e2->Translate(0, -1);
		}
		Renderer::GetInstance()->Draw(*screen, e2);
		Renderer::GetInstance()->ShowOutput(*screen);
		screen->ClearScreen();
	}	
	Renderer::GetInstance()->Draw(*screen, e);
	
	Renderer::GetInstance()->Draw(*screen, e3);
	Renderer::GetInstance()->Draw(*screen, e4);
	Renderer::GetInstance()->ShowOutput(*screen);
	system("pause");
	//Game::Init();

	//Game::Loop();

	//Game::Destroy();
	
	system("pause");
	delete s2;
	delete s3;
	delete s4;
	delete s;
	delete e;
	delete e2;
	delete e3;
	delete e4;
	delete screen;
	return 0;
}