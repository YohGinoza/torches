#pragma once
#include <string>
#include <vector>

class Sprite
{
public:	
	Sprite();
	Sprite(const std::string& path);
	~Sprite();
	std::pair<int, int> m_Dimension;
	std::vector<std::string> m_Image;
};

