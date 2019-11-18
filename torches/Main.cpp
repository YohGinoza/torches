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
	SpriteManager sm();
	SpriteManager::GetInstance()->PushBack(new Sprite("s1", "BitMapSprites/sprite_u1.txt"));
	SpriteManager::GetInstance()->PushBack(new Sprite("s2", "BitMapSprites/BeastAlpha.txt"));
	SpriteManager::GetInstance()->PushBack(new Sprite("s3", "BitMapSprites/BeastNu.txt"));
	SpriteManager::GetInstance()->PushBack(new Sprite("s3", "BitMapSprites/phelop.txt"));

	Entity* e1 = new Entity(SpriteManager::GetInstance()->GetSprite("s1"), std::make_pair(0, 0));
	Entity* e2 = new Entity(SpriteManager::GetInstance()->GetSprite("s3"), std::make_pair(0, 0));
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
		Renderer::GetInstance()->Draw(*screen, e1);
		Renderer::GetInstance()->Draw(*screen, e2);
		Renderer::GetInstance()->ShowOutput(*screen);
		screen->ClearScreen();
	}	
	Renderer::GetInstance()->ShowOutput(*screen);
	system("pause");
	//Game::Init();

	//Game::Loop();

	//Game::Destroy();
	
	system("pause");
	delete e1;
	delete e2;
	delete screen;
	return 0;
}