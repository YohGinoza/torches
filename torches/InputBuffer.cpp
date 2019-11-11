#include "InputBuffer.h"

InputBuffer* InputBuffer::instance_ = nullptr;

InputBuffer::InputBuffer() {}

InputBuffer* InputBuffer::instance() {
	if (instance_ == nullptr) {
		instance_ = new InputBuffer();
	}
	return instance_;
}

void InputBuffer::push(char c) {
	// std::cout << "Pushing." << std::endl;
	buffer.push_back(c);
}

char InputBuffer::pull() {
	// std::cout << "Pulling." << std::endl;
	char tmp = instance()->buffer.front();
	buffer.pop_front();
	return tmp;
}

bool InputBuffer::getEmpty() {
	return buffer.empty();
}

void InputBuffer::destroy() {
	if (instance_ != nullptr) {
		delete instance_;
	}
}