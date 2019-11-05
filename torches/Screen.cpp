#include "Screen.h"
#include <iostream>


Screen::Screen(int width, int height)
{
	this->ScreenWidth = width;
	this->ScreenHeight = height;

	// empty line
	for (int i = 0; i < ScreenWidth; i++) {
		m_EmptyLine += ' ';
	}
	// set blank screen
	for (int i = 0; i < ScreenHeight; i++) {
		ScreenWindow.push_back(m_EmptyLine);
	}
}

Screen::~Screen()
{
}

void Screen::ClearScreen() {
	for (int i = 0; i < ScreenHeight; i++) {
		ScreenWindow[i] = this->m_EmptyLine;
	}
}

int Screen::GetScreenHeight()const {
	return this->ScreenHeight;
}

int Screen::GetScreenWidth()const {
	return this->ScreenWidth;
}

void Screen::SetData(int row, int column, char c) {
	this->ScreenWindow[row][column] = c;
}

std::string Screen::GetScanline(int i) {
	return this->ScreenWindow[i];
}