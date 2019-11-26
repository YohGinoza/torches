#include "Sprite.h"
#include <fstream>
#include <iostream>

Sprite::Sprite()
{
	this->m_BitOff = ' ';
	this->m_BitOn = '#';	
}

Sprite::Sprite(const std::string& name, const std::string& path, int spriteType) {
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
		this->m_SpriteType = spriteType;
		if (spriteType == SpriteType::Bit) {			
			std::string buffer;
			while (!dataFile.eof()) {
				buffer.clear();
				std::getline(dataFile, buffer);
				if (buffer.size() > tmp_width) {
					tmp_width = buffer.size();
				}
				this->m_ImageData.push_back(std::bitset<64>(buffer).to_ullong());
			}
			this->m_Dimension = std::make_pair(tmp_width, this->m_ImageData.size());
		}
		else if (spriteType == SpriteType::Default) {			
			std::string buffer;
			while (!dataFile.eof()) {
				buffer.clear();
				std::getline(dataFile, buffer);
				if (buffer.size() > tmp_width) {
					tmp_width = buffer.size();
				}
				this->m_Image.push_back(buffer);
			}
			this->m_Dimension = std::make_pair(tmp_width, this->m_Image.size());			
		}
		
	}
}

void Sprite::Print() {
	for (int i = 0; i < this->m_ImageData.size(); i++) {
		std::cout << std::to_string(this->m_ImageData[i]) << std::endl;
	}
	std::cout << "====" << std::endl;
	for (int i = 0; i < this->m_Image.size(); i++) {
		std::cout << this->m_Image[i] << std::endl;
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

int Sprite::GetSpriteType() const {
	return this->m_SpriteType;
}

SpriteAnimation::SpriteAnimation() {

}

SpriteAnimation::~SpriteAnimation() {

}

SpriteAnimation::SpriteAnimation(const std::string& name, const std::string& path, int xFrames, int yFrames)
	:Sprite(name,path,1)
{
	this->m_xFrames = xFrames;
	this->m_yFrames = yFrames;
	this->m_FrameXCounter = 0;
	this->m_FrameYCounter = 0;
}

void SpriteAnimation::IncrementFrame() {
	this->m_FrameXCounter++;
	if (this->m_FrameXCounter > this->m_xFrames - 1) {
		this->m_FrameXCounter = 0;
		this->m_FrameYCounter++;
		if (this->m_FrameYCounter > this->m_yFrames - 1) {
			this->m_FrameYCounter = 0;
		}
	}
}

int SpriteAnimation::GetTotalXFrames() const {
	return this->m_xFrames;
}

int SpriteAnimation::GetTotalYFrames() const {
	return this->m_yFrames;
}

std::pair<int,int> SpriteAnimation::GetCurrentFrame() const {
	return std::make_pair(this->m_FrameXCounter,this->m_FrameYCounter);
}

int SpriteAnimation::GetWidthPerFrame() const {
	return (this->m_Dimension.first / this->m_xFrames);
}

int SpriteAnimation::GetHeightPerFrame() const {	
	return (this->m_Dimension.second / this->m_yFrames);
}

void SpriteAnimation::ResetAnimation() {
	this->m_FrameXCounter = 0;
	this->m_FrameYCounter = 0;
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
	std::cout << "Cannot find sprite name: " << spriteName << std::endl;
	return nullptr;
}

bool SpriteManager::PushBack(Sprite* sprite) {	
	this->m_SpriteBucket.push_back(sprite);
	return true;
}


void SpriteManager::LoadInputSprites() {
	for (int i = 0; i < 10; i++) {
		std::string pathName("BitMapSprites/sprite_input_");
		pathName += std::to_string(i);
		pathName += ".txt";
		this->m_SpriteBucket.push_back(new Sprite("sprite_input_" + std::to_string(i), pathName));		
	}

	for (int i = 36; i < 40; i++) {
		std::string pathName("BitMapSprites/sprite_input_");
		pathName += std::to_string(i);
		pathName += ".txt";
		this->m_SpriteBucket.push_back(new Sprite("sprite_input_" + std::to_string(i), pathName));
	}
}