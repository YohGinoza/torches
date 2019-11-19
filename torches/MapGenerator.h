#pragma once

#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

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
	int GetIndex(MapPosition pos);
	void PrintMap();
	void Test();
private:
	unsigned char* m_MapInfo;
	int m_VisitedNodes;
	std::vector<MapPosition> m_PositionStack;
};

