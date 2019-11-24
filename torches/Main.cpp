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
	"?";
	Screen* screen = new Screen(230, 60);
	Screen* screen_2 = new Screen(100, 50);
	Sprite* bg = new Sprite("bg", "BitMapSprites/titleScreen.txt",1);
	Sprite* bg_t = new Sprite("bg_torches", "BitMapSprites/title_torches.txt", 1);
	Sprite* e = new Sprite("enemy", "BitMapSprites/pumpkin.txt");
	SpriteAnimation* f = new SpriteAnimation("fire", "BitMapSprites/flame.txt",4,3);
	SpriteAnimation* f2 = new SpriteAnimation("fire2", "BitMapSprites/flame.txt", 4, 3);
	Sprite* s = new Sprite("s", "BitMapSprites/flame.txt",1);
	int screenCenter = -(e->m_Dimension.first*0.5) + (screen->GetScreenWidth()*0.5);
	
	Renderer::GetInstance()->DrawFull(*screen, std::make_pair((screen->GetScreenWidth()*0.5) - (bg->m_Dimension.first*0.5), 0), bg);
	Renderer::GetInstance()->DrawFull(*screen, std::make_pair((screen->GetScreenWidth()*0.5) - (bg_t->m_Dimension.first*0.5), 40), bg_t);
	Renderer::GetInstance()->DrawAnimation(*screen, std::make_pair(0, 40), f);
	Renderer::GetInstance()->DrawAnimation(*screen, std::make_pair(screen->GetScreenWidth() - f->GetWidthPerFrame(), 40), f2);

	for (int i = 0; i < screen_2->GetScreenHeight(); i++) {
		for (int j = 0; j < screen_2->GetScreenWidth(); j++) {
			screen_2->SetData(i, j, '=');
		}
	}
	

	Renderer::GetInstance()->ShowOutput(*screen);	
	system("pause");
	
	char input;
	std::cin >> input;	
	while (1) {
		system("cls");
		screen->ClearScreen();
		Renderer::GetInstance()->DrawFull(*screen, std::make_pair((screen->GetScreenWidth()*0.5) - (bg->m_Dimension.first*0.5), 0), bg);
		Renderer::GetInstance()->DrawFull(*screen, std::make_pair((screen->GetScreenWidth()*0.5) - (bg_t->m_Dimension.first*0.5), 40), bg_t);
		Renderer::GetInstance()->DrawAnimation(*screen, std::make_pair(0, 40), f);
		Renderer::GetInstance()->DrawAnimation(*screen, std::make_pair(screen->GetScreenWidth() - f->GetWidthPerFrame(), 40), f2);
		if (input == '0') {
			screen->CombineScreen(*screen_2, std::make_pair(0, 0));
		}
		Renderer::GetInstance()->ShowOutput(*screen);		
		system("pause");
	}
	srand(time(NULL));
	
	Game::Init();
	
	Game::Loop();
	
	Game::Exit();
	
	Game::Destroy();
	
	system("pause");
	
	return 0;
}