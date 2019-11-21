#pragma once
#include <string>
#include <vector>
#include <bitset>
class Sprite
{
	enum SpriteType {
		Bit = 0,
		Default
	};
public:
	Sprite();
	Sprite(const std::string& name, const std::string& path, int = SpriteType::Bit);
	~Sprite();
	std::pair<int, int> m_Dimension;
	std::vector<unsigned long long> m_ImageData;
	std::vector<std::string> m_Image;
	void SetBitOnChar(char c);
	char GetBitOnChar() const;
	void SetBitOffChar(char c);
	char GetBitOffChar() const;
	std::string GetName() const;
	void Print();	
protected:
	std::string m_Name;
	char m_BitOn;
	char m_BitOff;
};

class SpriteManager {
public:
	SpriteManager();
	~SpriteManager();
	Sprite* GetSprite(std::string spriteName);
	bool PushBack(Sprite* sprite);	
	static SpriteManager* GetInstance();
	void LoadInputSprites();
private:
	static SpriteManager* s_Instance;	
	static std::vector<Sprite*> m_SpriteBucket;
};