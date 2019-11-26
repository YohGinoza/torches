#include "InputReader.h"
#include "Game.h"

std::mutex mRead;

void InputReader::operator()() {
	mRead.lock();

	char c;

	do {
		c = _getch();
		if (c == '\r') {
			InputBuffer::instance()->push('\n');
		}
		else {
			InputBuffer::instance()->push(c);
		}

	} while (Game::getState() != Game::GameState::QUIT);

	InputBuffer::instance()->push(c);
	mRead.unlock();

}