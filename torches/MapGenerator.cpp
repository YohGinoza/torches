#include "MapGenerator.h"

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

MapGenerator::MapGenerator()
{
	m_MapInfo = new unsigned char[MAP_WIDTH * MAP_HEIGHT];
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		m_MapInfo[i] = 0;
	}
	m_VisitedNodes = 0;
}

MapGenerator::~MapGenerator()
{
	delete[] m_MapInfo;
}

void MapGenerator::GenerateMap()
{
	MapPosition currentPos;
	m_PositionStack.push_back(currentPos(rand() % 5, rand() % 5));
	m_MapInfo[GetIndex(currentPos)] |= NODE_VISITED;
	m_VisitedNodes++;

//	std::cout << "starting : " << m_PositionStack.back().x << ", " << m_PositionStack.back().y << std::endl;

	// NORTH, EAST, SOUTH, WEST
	MapPosition directions[4] = { MapPosition(0, -1), MapPosition(1, 0),
		MapPosition(0, 1), MapPosition(-1, 0) };

	while (m_VisitedNodes < (MAP_WIDTH * MAP_HEIGHT))
	{
	//	std::cout << "width : " << MAP_WIDTH << ", height : " << MAP_HEIGHT << std::endl;

		currentPos = m_PositionStack.back();
		std::vector<int> adjacents;
		for (int i = 0; i < 4; i++) {
			int offset = GetIndex(currentPos + directions[i]);
			if (offset != -1 && (m_MapInfo[offset] & NODE_VISITED) == 0) {
				adjacents.push_back(i);
			}
		}

	//	std::cout << "Print adjacent size : " << adjacents.size() << std::endl;

		if (adjacents.size() != 0) {
			// random which node to choose from available adjacents
			int nextDir = adjacents[rand() % adjacents.size()];
			switch (nextDir)
			{
			case DIR_N:
			//	std::cout << "chose north" << std::endl;
				m_MapInfo[GetIndex(currentPos)] |= NODE_PATH_N;
				m_MapInfo[GetIndex(currentPos + directions[DIR_N])] |= NODE_PATH_S;
			//	std::cout << "current node : " << currentPos.x << ", " << currentPos.y << std::endl;
			//	std::cout << "next node : " << (currentPos + directions[DIR_N]).x << ", " << (currentPos + directions[DIR_N]).y << std::endl;
				break;
			case DIR_E:
			//	std::cout << "chose east" << std::endl;
				m_MapInfo[GetIndex(currentPos)] |= NODE_PATH_E;
				m_MapInfo[GetIndex(currentPos + directions[DIR_E])] |= NODE_PATH_W;
			//	std::cout << "current node : " << currentPos.x << ", " << currentPos.y << std::endl;
			//	std::cout << "next node : " << (currentPos + directions[DIR_E]).x << ", " << (currentPos + directions[DIR_E]).y << std::endl;
				break;
			case DIR_S:
			//	std::cout << "chose south" << std::endl;
				m_MapInfo[GetIndex(currentPos)] |= NODE_PATH_S;
				m_MapInfo[GetIndex(currentPos + directions[DIR_S])] |= NODE_PATH_N;
			//	std::cout << "current node : " << currentPos.x << ", " << currentPos.y << std::endl;
			//	std::cout << "next node : " << (currentPos + directions[DIR_S]).x << ", " << (currentPos + directions[DIR_S]).y << std::endl;
				break;
			case DIR_W:
			//	std::cout << "chose west" << std::endl;
				m_MapInfo[GetIndex(currentPos)] |= NODE_PATH_W;
				m_MapInfo[GetIndex(currentPos + directions[DIR_W])] |= NODE_PATH_E;
			//	std::cout << "current node : " << currentPos.x << ", " << currentPos.y << std::endl;
			//	std::cout << "next node : " << (currentPos + directions[DIR_W]).x << ", " << (currentPos + directions[DIR_W]).y << std::endl;
				break;
			}
			m_PositionStack.push_back(currentPos + directions[nextDir]);
			m_MapInfo[GetIndex(m_PositionStack.back())] |= NODE_VISITED;
		//	std::cout << "next node : " << m_PositionStack.back().x << ", " << m_PositionStack.back().y << std::endl;
			m_VisitedNodes++;
		//	std::cout << "visited : " << m_VisitedNodes << std::endl << std::endl;
		}
		else {
			m_PositionStack.pop_back();
		}
	}

	int torchCount = 0;
	int chestCount = 0;

	while (torchCount < TORCH_COUNT)
	{
		for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
		{
			if (rand() % 25 == 0)
			{
				m_MapInfo[i] |= NODE_TYPE_T;
				torchCount++;
			}
			if (torchCount >= TORCH_COUNT)
			{
				break;
			}
		}
	}

	while (chestCount < CHEST_COUNT)
	{
		for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
		{
			if (rand() % 25 == 0)
			{
				if ((m_MapInfo[i] & NODE_TYPE_T) == 0) {
					m_MapInfo[i] |= NODE_TYPE_C;
					chestCount++;
				}
			}
			if (chestCount >= CHEST_COUNT)
			{
				break;
			}
		}
	}
}

void MapGenerator::Load(const std::string& fileName)
{
	std::ifstream loadFile(fileName);
	if (!loadFile.is_open())
	{
		std::cout << "Error opening file for read." << std::endl;
	}
	else
	{
		while (!loadFile.eof()) {
			for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
			{
				loadFile >> m_MapInfo[i];
			}
		}
	}
	loadFile.close();
}

void MapGenerator::Save(const std::string& fileName)
{
	std::ofstream saveFile(fileName);
	if (!saveFile.is_open())
	{
		std::cout << "Error opening file for write." << std::endl;
	}
	else
	{
		for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
		{
			saveFile << m_MapInfo[i];
		}
	}
	saveFile.close();
}

int MapGenerator::GetIndex(MapPosition pos)
{
	if (pos.x > -1 && pos.x < MAP_WIDTH && pos.y > -1 && pos.y < MAP_HEIGHT)
	{
		return (pos.y * MAP_WIDTH) + pos.x;
	}
	else
	{
		return -1;
	}
}

void MapGenerator::PrintMap()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				for (int x = 0; x < 3; x++)
				{
					if ( (i != 0 && y == 0 && x == 1 && (m_MapInfo[GetIndex(MapPosition(j, i))] & NODE_PATH_N)) ||
						(i != MAP_HEIGHT - 1 && y == 2 && x == 1 && (m_MapInfo[GetIndex(MapPosition(j, i))] & NODE_PATH_S)) )
					{
						std::cout << "| ";
					}
					else if ( (j != 0 && x == 0 && y == 1 && (m_MapInfo[GetIndex(MapPosition(j, i))] & NODE_PATH_W)) ||
						(j != MAP_WIDTH - 1 && x == 2 & y == 1 && (m_MapInfo[GetIndex(MapPosition(j, i))] & NODE_PATH_E)) )
					{
						std::cout << "- ";
					}
					else if (x == 1 && y == 1)
					{
						if (m_MapInfo[GetIndex(MapPosition(j, i))] & NODE_TYPE_C)
						{
							std::cout << "C ";
						}
						else if (m_MapInfo[GetIndex(MapPosition(j, i))] & NODE_TYPE_T)
						{
							std::cout << "T ";
						}
						else
						{
							std::cout << "N ";
						}
					}
					else {
						std::cout << "  ";
					}
				}
			}
			std::cout << std::endl;
		}
	}
}

void MapGenerator::Test()
{
	GenerateMap();
	PrintMap();
}