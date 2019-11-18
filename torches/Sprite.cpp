#include "Sprite.h"
#include <fstream>
#include <iostream>

Sprite::Sprite()
{
	this->m_BitOff = ' ';
	this->m_BitOn = '#';	
}

Sprite::Sprite(const std::string& name, const std::string& path) {
	this->m_BitOff = ' ';
	this->m_BitOn = '#';
	this->m_Name = name;
	std::ifstream dataFile(path);
	int tmp_width = 0;
	if (!dataFile.is_open()) {
		std::cout << "Cannot open file" << std::endl;
	}
	else {
		std::cout << "Successfully opened " << path << std::endl;
		std::string buffer;
		while (!dataFile.eof()) {
			buffer.clear();
			std::getline(dataFile, buffer);
			tmp_width = buffer.size();
			std::cout << buffer << std::endl;
			std::cout << "==" <<  tmp_width << std::endl;
			std::cout << std::bitset<64>(buffer).to_string() << std::endl;
			this->m_ImageData.push_back(std::bitset<64>(buffer).to_ullong());
		}		
		this->m_Dimension = std::make_pair(tmp_width, this->m_ImageData.size());
		std::cout << tmp_width << " " << this->m_ImageData.size() << std::endl;
	}
}

void Sprite::Print() {
	for (int i = 0; i < this->m_ImageData.size(); i++) {
		std::cout << std::to_string(this->m_ImageData[i]) << std::endl;
	}
}

Sprite::~Sprite()
{
}

void Sprite::SetBitOnChar(char c) {
	this->m_BitOn = c;
}

char Sprite::GetBitOnChar() const {
	return this->m_BitOn;
}

void Sprite::SetBitOffChar(char c) {
	this->m_BitOff = c;
}

char Sprite::GetBitOffChar() const {
	return this->m_BitOff;
}

std::string Sprite::GetName() const {
	return this->m_Name;
}