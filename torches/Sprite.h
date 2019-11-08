#pragma once
#include <string>
#include <vector>
#include <bitset>
class Sprite
{
public:	
	Sprite();
	Sprite(const std::string& path);
	~Sprite();
	std::pair<int, int> m_Dimension;
	std::vector<std::string> m_Image;
	//std::vector<std::bitset<8>> m_ImageData;
};

