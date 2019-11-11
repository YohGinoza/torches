#include <stdio.h>
#include <windows.h>   // WinApi header
#include <iostream>
#include <string>
#include <time.h>
#include "Entity.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Screen.h"
#include "InputBuffer.h"
#include "InputReader.h"
#include "InputWriter.h"

// example function for real-time input
// esc to exit
/*
void testInput()
{
	InputReader reader;
	InputWriter writer;

	std::thread readerThread = std::thread(reader);
	std::thread writerThread = std::thread(writer);

	if (readerThread.joinable()) {
		readerThread.join();
	}
	if (writerThread.joinable()) {
		writerThread.join();
	}

	InputBuffer::instance()->destroy();
}
*/

int main()
{
	//HANDLE  hConsole;
	//int k;

	//hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//// you can loop k higher to see more color choices
	//for (k = 1; k < 255; k++)
	//{
	//	SetConsoleTextAttribute(hConsole, 3);
	//	printf("%3d  %s\n", k, "I want to be nice today!");
	//	std::cout << "oekr;alskdf;lj" << std::endl;
	//}
	//std::string world;

	//getchar();  // wait
	//return 0;

	Screen* screen = new Screen(64, 32);
	Renderer r();
	Sprite* l_sprite = new Sprite();
	Entity* l_entity = new Entity(l_sprite);
	for (int i = 0; i < l_entity->m_Sprite->m_Dimension.second; i++) {
		for (int j = 0; j < l_entity->m_Sprite->m_Dimension.first; j++) {
			std::cout << l_entity->m_Sprite->m_Image[i][j];
		}
		std::cout << std::endl;
	}
	system("pause");
	//Renderer::GetInstance()->Draw(*screen, l_entity);
	int left = 0;
	int right = 0;
	bool move_dir = false;
	while (1) {
		if (!move_dir && left < 5) {			
			left++;
			l_entity->Translate(1, 1);
			if (left >= 5) {
				right = 0;
				move_dir = true;
			}
		}
		else if(move_dir && right < 5){			
			right++;
			l_entity->Translate(-1, -1);				
			if (right >= 5) {
				left = 0;
				move_dir = false;
			}
		}
		system("cls");
		screen->ClearScreen();
		Renderer::GetInstance()->Draw(*screen, l_entity);
		/*
		char move;
		std::cin >> move;
		switch (move) {
		case '4':
		case 'a':
			// left
			l_entity->Translate(-1, 0);
			break;
		case '6':
		case 'd':
			// right
			l_entity->Translate(1, 0);
			break;
		case '8':
		case 'w':
			// up
			l_entity->Translate(0, -1);
			break;
		case '2':
		case 'e':
			// down
			l_entity->Translate(0, 1);
			break;
		default:
			break;
		}		
		*/
	}
	delete l_sprite;
	system("pause");
	return 0;
}