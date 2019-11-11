#include "InputReader.h"

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
	} while (c != '\033');
	InputBuffer::instance()->push(c);


	mRead.unlock();

}