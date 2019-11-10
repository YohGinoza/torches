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
	void SetBitOnChar(char c);
	char GetBitOnChar() const;
	void SetBitOffChar(char c);
	char GetBitOffChar() const;
protected:
	char m_BitOn;
	char m_BitOff;
};

