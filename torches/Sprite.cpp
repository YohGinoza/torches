#include "Sprite.h"
#include <fstream>
#include <iostream>

Sprite::Sprite()
{
	
}

Sprite::Sprite(const std::string& path) {
	std::ifstream dataFile(path);
	if (!dataFile.is_open()) {
		std::cout << "Cannot open file" << std::endl;
	}
	else {
		std::cout << "Successfully opened " << path << std::endl;		
		while (!dataFile.eof()) {
			std::string buffer;
			std::getline(dataFile, buffer);
			this->m_Image.push_back(buffer);
			break;
		}
		this->m_Dimension = std::make_pair(this->m_Image.size(), this->m_Image[0].size());
	}

	// TODO
	//this->m_Dimension = std::make_pair(11, 11);
}

Sprite::~Sprite()
{
}
