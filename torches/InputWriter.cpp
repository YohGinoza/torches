#include "InputWriter.h"

std::mutex mWrite;

void InputWriter::operator()() {
	mWrite.lock();
	while (true) {
		time_t timet = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		struct tm time;
		localtime_s(&time, &timet);
		//std::cout << std::put_time(&time, "%X") << ": ";
		if (!InputBuffer::instance()->getEmpty()) {
			char c = InputBuffer::instance()->pull();
			if (c != '\033') {
				std::cout << c;
			}
			else {
				break;
			}
		}
		//std::cout << std::endl;
	}
	mWrite.unlock();
}