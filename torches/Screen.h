#pragma once

#include <string>
#include <vector>

class Screen
{
public:
	Screen(int width, int height);
	~Screen();
	//void Effect_Interlace();
	int GetScreenWidth()const;
	int GetScreenHeight()const;	
	void ClearScreen();
	void SetData(int row, int column, char c);
	std::string GetScanline(int i);
	void CombineScreen(Screen& screen, std::pair<int, int> upperleftCorner);
private:
	std::vector<std::string> ScreenWindow;
	std::string m_EmptyLine;
	int ScreenWidth;
	int ScreenHeight;	
};

