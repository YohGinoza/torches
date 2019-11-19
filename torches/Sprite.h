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
	std::vector<unsigned long long> m_ImageData;
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