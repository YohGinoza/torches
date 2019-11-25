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

void Screen::CombineScreen(Screen& screen, std::pair<int,int> upperleftCorner) {
	if (upperleftCorner.first > this->ScreenWidth ||
		upperleftCorner.second > this->ScreenHeight ||
		upperleftCorner.first + screen.GetScreenWidth() < 0 ||
		upperleftCorner.second + screen.GetScreenHeight() < 0) {
		return;
	}
	int screenRow = 0;
	int screenCol = 0;
	for (int i = upperleftCorner.second; i < upperleftCorner.second + screen.GetScreenHeight(); i++, screenRow++) {
		screenCol = 0;
		for (int j = upperleftCorner.first; j < upperleftCorner.first + screen.GetScreenWidth(); j++, screenCol++) {
			if (i > this->ScreenHeight || j > this->ScreenWidth || i < 0 ||	j < 0) {
				continue;
			}
			this->SetData(i, j, screen.GetScanline(screenRow)[screenCol]);
		}
	}
}