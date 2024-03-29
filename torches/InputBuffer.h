#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include <iostream>
#include <list>

#define KEYCODE_NUM 41

enum KeyCode {
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,

	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,

	KEY_RIGHT,
	KEY_LEFT,
	KEY_DOWN,
	KEY_UP,
	
	KEY_ESC
};


class InputBuffer
{
private:
	static InputBuffer* instance_;
	InputBuffer();
	std::list<char> buffer;

	bool input[KEYCODE_NUM];
	bool Keypress;
public:
	static InputBuffer* instance();
	void push(char c);
	char pull();
	bool getEmpty();
	void destroy();
	void clearList();
	void clearArray();
	void updateInput();


	bool getKey(int keycode);
	bool KeyPress();
};
#endif