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
	Sprite(const std::string& name, const std::string& path, int spriteType = SpriteType::Bit);
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
	int GetSpriteType() const;
protected:
	std::string m_Name;
	int m_SpriteType;
	char m_BitOn;
	char m_BitOff;
};

class SpriteAnimation : public Sprite {
public:
	SpriteAnimation();
	SpriteAnimation(const std::string& name, const std::string& path, int xFrames, int yFrames);	
	~SpriteAnimation();
	void IncrementFrame();
	int GetTotalXFrames() const;
	int GetTotalYFrames() const;
	std::pair<int,int> GetCurrentFrame() const;
	int GetWidthPerFrame() const;
	int GetHeightPerFrame() const;	
private:
	int m_FrameXCounter;
	int m_FrameYCounter;
	int m_xFrames;
	int m_yFrames;

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