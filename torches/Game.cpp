#include "Game.h"

#include <vector>
#include <iostream>

namespace Game 
{
	InputReader reader;

	std::thread readerThread;
	InputBuffer* input;

	//see this func below to see the example to use input
	void debug_input();
	//How to USE in other code
	//haven't check this with other code yet so if you try this and it not work tellme :D Iypht desu yay
	/*
		Game::getInput()->getKey(KEY_1);
	*/

	void Init() 
	{
		input = InputBuffer::instance();
		readerThread = std::thread(reader);
	}

	void Update() 
	{
		input->updateInput();

		//can call game logic loop around here

		//GAMELOGIC();

		//RENDER();

		///////////////////////////////////////

		debug_input();


		input->clearArray();
	}

	void Loop() 
	{
		while (true) 
		{
			Update();
		}
	}

	void Destroy() 
	{
		if (readerThread.joinable()) {
			readerThread.join();
		}
		
		InputBuffer::instance()->destroy();
	}
	
	InputBuffer* getInput() {
		return input;
	}

	void debug_input() {
		
		if (input->getKey(KEY_W))
		{
			std::cout << "W\n";
		}

		if (input->getKey(KEY_A))
		{
			std::cout << "A\n";
		}

		if (input->getKey(KEY_S))
		{
			std::cout << "S\n";
		}

		if (input->getKey(KEY_D))
		{
			std::cout << "D\n";
		}

		if (input->getKey(KEY_1))
		{
			std::cout << "1\n";
		}

		if (input->getKey(KEY_LEFT))
		{
			std::cout << "LEFT\n";
		}

		if (input->getKey(KEY_RIGHT))
		{
			std::cout << "RIGHT\n";
		}

		if (input->getKey(KEY_UP))
		{
			std::cout << "UP\n";
		}

		if (input->getKey(KEY_DOWN)) {
			std::cout << "DOWN\n";
		}
	}

}