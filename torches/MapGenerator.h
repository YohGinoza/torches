#pragma once

#include <vector>
#include <string>

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();
	std::vector<int*> GenerateMap(int width, int height, int rooms);
	void Load(const std::string& fileName);
	void Save(const std::string& fileName);
private:
	std::vector<int*> m_MapInfo;
};

