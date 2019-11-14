#pragma once
#include <string>
#include <vector>
#include <bitset>
class Sprite
{
public:	
	Sprite();
	Sprite(const std::string& name, const std::string& path);
	~Sprite();
	std::pair<int, int> m_Dimension;
	//std::vector<std::string> m_Image;
	std::vector<unsigned int> m_ImageData;
	void SetBitOnChar(char c);
	char GetBitOnChar() const;
	void SetBitOffChar(char c);
	char GetBitOffChar() const;
	std::string GetName() const;
protected:
	std::string m_Name;
	char m_BitOn;
	char m_BitOff;
};

