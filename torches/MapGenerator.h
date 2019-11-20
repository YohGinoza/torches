#pragma once

#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#define MAP_WIDTH 5
#define MAP_HEIGHT 5

#define TORCH_COUNT 10
#define CHEST_COUNT 5

enum
{
	NODE_PATH_N = 0x01,
	NODE_PATH_E = 0x02,
	NODE_PATH_S = 0x04,
	NODE_PATH_W = 0x08,
	NODE_VISITED = 0x10,
	NODE_TYPE_C = 0x20,
	NODE_TYPE_T = 0x40
};

enum
{
	DIR_N = 0,
	DIR_E,
	DIR_S,
	DIR_W
};

class MapPosition
{
public:
	int x;
	int y;
	MapPosition() : x(0), y(0) {}
	MapPosition(int x, int y) : x(x), y(y) {}
	MapPosition operator()(int x, int y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}
	MapPosition operator+(MapPosition const &other)
	{
		MapPosition tmp;
		tmp(this->x + other.x, this->y + other.y);
		return tmp;
	}
	MapPosition operator-(MapPosition const &other)
	{
		MapPosition tmp;
		tmp(this->x - other.x, this->y - other.y);
		return tmp;
	}
};

class MapGenerator
{
public:
	MapGenerator();
	~MapGenerator();
	void GenerateMap();
	void Load(const std::string& fileName);
	void Save(const std::string& fileName);
	
	unsigned char* getMapInfo();

	int GetIndex(MapPosition pos);
	void PrintMap();
	void Test();
private:
	unsigned char* m_MapInfo;
	int m_VisitedNodes;
	std::vector<MapPosition> m_PositionStack;
};

