#include "InputBuffer.h"

InputBuffer* InputBuffer::instance_ = nullptr;

InputBuffer::InputBuffer() {
	clearArray();

	for (int i = 0; i < 5; i++) {
		push('\0');
	}
}

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
	if (!buffer.empty()) {
		char tmp = instance()->buffer.front();
		buffer.pop_front();

		return tmp;
	}
}

bool InputBuffer::getEmpty() {
	return buffer.empty();
}

void InputBuffer::destroy() {
	if (instance_ != nullptr) {
		delete instance_;
	}
}

void InputBuffer::clearList() {
	buffer.clear();
}

void InputBuffer::clearArray() 
{
	for (int i = 0; i < KEYCODE_NUM; i++)
	{
		input[i] = false;
	}

	Keypress = false;
}

void InputBuffer::updateInput() 
{ 
	while(!getEmpty())
	{
		int c = pull();

		if (c >= 'a' && c <= 'z') 
		{
			input[c - 87] = true;

			Keypress = true;
		}
		else if(c >= '0' && c <= '9')
		{
			input[c - 48] = true;

			Keypress = true;
		}
		else if (c == 72) 
		{
			input[c - 33] = true;

			Keypress = true;
		}
		else if (c == 75) 
		{
			input[c -38] = true;

			Keypress = true;
		}
		else if (c == 77) {
			input[c - 41] = true;

			Keypress = true;
		}
		else if (c == 80) {
			input[c - 42] = true;

			Keypress = true;
		}
		else if (c == '\033') {
			input[40] = true;
		}
	}
}

bool InputBuffer::getKey(int keycode) 
{
	return input[keycode];
}

bool InputBuffer::KeyPress() 
{
	return Keypress;
}