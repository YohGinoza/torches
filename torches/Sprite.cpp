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
			this->m_ImageData.push_back(std::bitset<64>(buffer).to_ullong());
		}		
		this->m_Dimension = std::make_pair(tmp_width, this->m_ImageData.size());
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

SpriteManager* SpriteManager::s_Instance = nullptr;
std::vector<Sprite*> SpriteManager::m_SpriteBucket;

SpriteManager::SpriteManager() {
	if (s_Instance == nullptr) {
		s_Instance = new SpriteManager();
	}
	else {
		delete this;
		return;
	}
}

SpriteManager::~SpriteManager() {
	for (int i = 0; i < this->m_SpriteBucket.size(); i++) {
		if (this->m_SpriteBucket[i] != nullptr) {
			delete this->m_SpriteBucket[i];
		}
	}
}

SpriteManager* SpriteManager::GetInstance() {
	return s_Instance;
}

Sprite* SpriteManager::GetSprite(std::string spriteName) {
	for (int i = 0; i < this->m_SpriteBucket.size(); i++) {
		if (this->m_SpriteBucket[i] != nullptr && this->m_SpriteBucket[i]->GetName() == spriteName) {
			return this->m_SpriteBucket[i];
		}
	}
	return nullptr;
}

bool SpriteManager::PushBack(Sprite* sprite) {	
	this->m_SpriteBucket.push_back(sprite);
	return true;
}


void SpriteManager::LoadInputSprite() {
	//std::ifstream dataFile(path);
	//int tmp_width = 0;
	//if (!dataFile.is_open()) {
	//	std::cout << "Cannot open file" << std::endl;
	//}
	//else {
	//	std::cout << "Successfully opened " << path << std::endl;
	//	std::string buffer;
	//	while (!dataFile.eof()) {
	//		buffer.clear();
	//		std::getline(dataFile, buffer);
	//		tmp_width = buffer.size();
	//		this->m_ImageData.push_back(std::bitset<64>(buffer).to_ullong());
	//	}
	//	this->m_Dimension = std::make_pair(tmp_width, this->m_ImageData.size());
	//}
}