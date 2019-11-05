#include "Sprite.h"
#include <fstream>
#include <iostream>

Sprite::Sprite()
{
	this->m_Image.push_back("0001111000");
	this->m_Image.push_back("0001001000");
	this->m_Image.push_back("0001001000");
	this->m_Image.push_back("1111111111");
	this->m_Image.push_back("1111111111");
	this->m_Image.push_back("0100000010");
	this->m_Image.push_back("1110000111");
	this->m_Image.push_back("1010000101");
	this->m_Image.push_back("1010000101");
	this->m_Image.push_back("1010000101");
	this->m_Image.push_back("1010000101");
	this->m_Dimension = std::make_pair(11, 11);
}

Sprite::Sprite(const std::string& path) {
	std::ifstream dataFile(path);
	if (!dataFile.is_open()) {
		std::cout << "Cannot open file" << std::endl;
	}
	else {
		std::cout << "Successfully opened " << path << std::endl;
		while (!dataFile.eof()) {
			// TODO
			break;
		}
	}

	// TODO
	//this->m_Dimension = std::make_pair(11, 11);
}

Sprite::~Sprite()
{
}
