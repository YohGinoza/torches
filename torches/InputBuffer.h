#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include <iostream>
#include <list>

class InputBuffer
{
private:
	static InputBuffer* instance_;
	InputBuffer();
	std::list<char> buffer;
public:
	static InputBuffer* instance();
	void push(char c);
	char pull();
	bool getEmpty();
	void destroy();
};
#endif