#ifndef INPUTWRITER_H
#define INPUTWRITER_H

#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>

#include "InputBuffer.h"

class InputWriter
{
public:
	void operator()();
};
#endif