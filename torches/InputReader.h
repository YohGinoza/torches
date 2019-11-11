#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <thread>
#include <mutex>
#include <conio.h>

#include "InputBuffer.h"

class InputReader
{
public:
	void operator()();
};
#endif