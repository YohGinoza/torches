#include "PhaseMaze.h"

PhaseMaze* PhaseMaze::s_Instance = nullptr;

PhaseMaze* PhaseMaze::GetInstance() {
	if (s_Instance == nullptr) {
		s_Instance = new PhaseMaze();
	}

	return s_Instance;
}

PhaseMaze::PhaseMaze()
{
	map = new char*[ROOM_HEIGHT];
	map_detect = new bool*[ROOM_HEIGHT];

	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		map[i] = new char[ROOM_WIDTH];
		map_detect[i] = new bool[ROOM_WIDTH];
	}

	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			map[i][j] = '.';
			map_detect[i][j] = false;
		}
	}

	mapGen = new MapGenerator();
	mapGen->GenerateMap();

	//Generate Room
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(j, i))] & NODE_TYPE_T)
			{
				m_Rooms[i][j] = new Room(TYPE_TORCHES, rand() % MON_PER_ROOM + MON_PER_ROOM / 2);
			}
			else if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(j, i))] & NODE_TYPE_C) 
			{
				m_Rooms[i][j] = new Room(TYPE_CHEST, rand() % MON_PER_ROOM + MON_PER_ROOM / 2);
			}
			else 
			{
				m_Rooms[i][j] = new Room(TYPE_EMPTY, rand() % MON_PER_ROOM + MON_PER_ROOM / 2);
			}
		}
	}

	mapGen->PrintMap();

	currRoomX = 0;
	currRoomY = 0;

	debug_draw = false;

	player = Player::GetInstance();

	player->SetPosition(2, ROOM_HEIGHT / 2);

	resetRoom();

	//std::cout << player->GetPosition().first << " " << player->GetPosition().second << std::endl;
	
	map[player->GetPosition().second][player->GetPosition().first] = '@';
}

void PhaseMaze::Draw_Debug() 
{
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++) 
		{
			if (map_detect[i][j]) 
			{
				std::cout << map[i][j];
			}
			else 
			{
				std::cout << ' ';
			}
		}

		std::cout << std::endl;
	}
}

void PhaseMaze::DrawMaze(Screen& screen) {
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			if (map_detect[i][j])
			{
				screen.SetData(i, j, map[i][j]);
			}
			else
			{
				screen.SetData(i, j, ' ');
			}
		}
	}
}


PhaseMaze::~PhaseMaze()
{
}

void PhaseMaze::OnUpdate(float dt, Screen& screen) 
{
	player_posX = player->GetPosition().first;
	player_posY = player->GetPosition().second;

	if (!debug_draw) {
		UpdateDetectRange();
		Draw_Debug();
		debug_draw = true;
	}

	if (Game::getInput()->KeyPress() || UpdateDraw)
	{
		system("cls");

		UpdateDraw = false;

		MoveMon();

		PlayerInput();

		std::cout << player_posX << " " << player_posY << std::endl;

		UpdateDetectRange();
		Draw_Debug();
	}
}

void PhaseMaze::PlayerInput()
{
	if (Game::getInput()->getKey(KeyCode::KEY_A))
	{
		if (/*(player_posX > 1) && */(map[player_posY][player_posX - 1] == '.'))
		{
			map[player_posY][player_posX] = '.';

			player->Translate(-1, 0);
			player_posX -= 1;
			map[player_posY][player_posX] = '@';
		}
	}
	else if (Game::getInput()->getKey(KeyCode::KEY_D))
	{
		if (/*(player_posX < ROOM_WIDTH - 2) && */(map[player_posY][player_posX + 1] == '.'))
		{
			map[player_posY][player_posX] = '.';

			player->Translate(1, 0);
			player_posX += 1;
			map[player_posY][player_posX] = '@';
		}
	}
	else if (Game::getInput()->getKey(KeyCode::KEY_W))
	{
		if (/*(player_posY > 1) && */(map[player_posY - 1][player_posX] == '.'))
		{
			map[player_posY][player_posX] = '.';

			player->Translate(0, -1);
			player_posY -= 1;
			map[player_posY][player_posX] = '@';
		}
	}
	else if (Game::getInput()->getKey(KeyCode::KEY_S))
	{
		if (/*(player_posY < ROOM_HEIGHT - 2) && */(map[player_posY + 1][player_posX] == '.'))
		{
			map[player_posY][player_posX] = '.';

			player->Translate(0, 1);
			player_posY += 1;
			map[player_posY][player_posX] = '@';
		}
	}
	else if (Game::getInput()->getKey(KeyCode::KEY_T))
	{
		m_Rooms[currRoomY][currRoomX]->LitTorches(true);
	}

	if (player_posY == 0) 
	{
		UpdateDraw = true;
		map[player_posY][player_posX] = '.';
		player->SetPosition(ROOM_WIDTH / 2, ROOM_HEIGHT - 2);

		map[player->GetPosition().second][player->GetPosition().first] = '@';

		currRoomY -= 1;
		resetRoom();
	}
	else if (player_posY == ROOM_HEIGHT - 1) 
	{
		UpdateDraw = true;
		map[player_posY][player_posX] = '.';
		player->SetPosition(ROOM_WIDTH / 2, 2);

		map[player->GetPosition().second][player->GetPosition().first] = '@';

		currRoomY += 1;
		resetRoom();
	}
	else if (player_posX == 0) 
	{
		UpdateDraw = true;
		map[player_posY][player_posX] = '.';
		player->SetPosition(ROOM_WIDTH - 2, ROOM_HEIGHT / 2);

		map[player->GetPosition().second][player->GetPosition().first] = '@';

		currRoomX -= 1;
		resetRoom();
	}
	else if (player_posX == ROOM_WIDTH - 1) 
	{
		UpdateDraw = true;
		map[player_posY][player_posX] = '.';
		player->SetPosition(2, ROOM_HEIGHT / 2);

		map[player->GetPosition().second][player->GetPosition().first] = '@';

		currRoomX += 1;
		resetRoom();
	}
}

void PhaseMaze::UpdateDetectRange() 
{
	ClearDetectRange();

	for (int i = player_posY - 1; i < player_posY + 2; i++)
	{
		for (int j = player_posX - 2; j < player_posX + 3; j++)
		{
			if ((i >= 0) && (i <= ROOM_HEIGHT - 1) && (j >= 0) && (j <= ROOM_WIDTH -1)) {

				map_detect[i][j] = true;
			}
		}
	}

	for (int i = player_posX - 1; i < player_posX + 2; i++)
	{
		if ((player_posY - 2 >= 0) && (player_posY - 2 <= ROOM_HEIGHT - 1) && (i >= 0) && (i <= ROOM_WIDTH - 1))
		{
			map_detect[player_posY - 2][i] = true;
		}

		if ((player_posY + 2 >= 0) && (player_posY + 2 <= ROOM_HEIGHT - 1) && (i >= 0) && (i <= ROOM_WIDTH - 1))
		{
			map_detect[player_posY + 2][i] = true;
		}
	}
}

void PhaseMaze::ClearDetectRange() 
{
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			map_detect[i][j] = false;
		}
	}

	map_detect[player->GetPosition().second][player->GetPosition().first] = true;

	if (!m_Rooms[currRoomY][currRoomX]->getTorches()) {
		for (int i = 0; i < ROOM_WIDTH; i++)
		{
			map_detect[0][i] = true;
			map_detect[ROOM_HEIGHT - 1][i] = true;
		}

		for (int i = 0; i < ROOM_HEIGHT; i++)
		{
			map_detect[i][0] = true;
			map_detect[i][ROOM_WIDTH - 1] = true;
		}

		if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(currRoomX, currRoomY))] & NODE_PATH_N)
		{
			map_detect[0][ROOM_WIDTH / 2] = false;
			map_detect[0][(ROOM_WIDTH / 2) + 1] = false;
			map_detect[0][(ROOM_WIDTH / 2) - 1] = false;
		}

		if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(currRoomX, currRoomY))] & NODE_PATH_S)
		{

			map_detect[ROOM_HEIGHT - 1][ROOM_WIDTH / 2] = false;
			map_detect[ROOM_HEIGHT - 1][(ROOM_WIDTH / 2) + 1] = false;
			map_detect[ROOM_HEIGHT - 1][(ROOM_WIDTH / 2) - 1] = false;
		}

		if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(currRoomX, currRoomY))] & NODE_PATH_E)
		{
			map_detect[ROOM_HEIGHT / 2][ROOM_WIDTH - 1] = false;
			map_detect[(ROOM_HEIGHT / 2) + 1][ROOM_WIDTH - 1] = false;
			map_detect[(ROOM_HEIGHT / 2) - 1][ROOM_WIDTH - 1] = false;
		}

		if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(currRoomX, currRoomY))] & NODE_PATH_W)
		{
			map_detect[ROOM_HEIGHT / 2][0] = false;
			map_detect[(ROOM_HEIGHT / 2) + 1][0] = false;
			map_detect[(ROOM_HEIGHT / 2) - 1][0] = false;
		}
	}
	else
	{
		for (int i = 0; i < ROOM_HEIGHT; i++)
		{
			for (int j = 0; j < ROOM_WIDTH; j++)
			{
				map_detect[i][j] = true;
			}
		}
	}
}

void PhaseMaze::resetRoom() {
	
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			map[i][j] = '.';
			map_detect[i][j] = false;
		}
	}

	map[player->GetPosition().second][player->GetPosition().first] = '@';

	for (int i = 0; i < ROOM_WIDTH; i++)
	{
		map[0][i] = '#';
		map[ROOM_HEIGHT - 1][i] = '#';
	}

	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		map[i][0] = '#';
		map[i][ROOM_WIDTH - 1] = '#';
	}

	if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(currRoomX, currRoomY))] & NODE_PATH_N)
	{
		map[0][ROOM_WIDTH / 2] = '.';
		map[0][(ROOM_WIDTH / 2) + 1] = '.';
		map[0][(ROOM_WIDTH / 2) - 1] = '.';
	}

	if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(currRoomX, currRoomY))] & NODE_PATH_S)
	{
		map[ROOM_HEIGHT - 1][ROOM_WIDTH / 2] = '.';
		map[ROOM_HEIGHT - 1][(ROOM_WIDTH / 2) + 1] = '.';
		map[ROOM_HEIGHT - 1][(ROOM_WIDTH / 2) - 1] = '.';
	}

	if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(currRoomX, currRoomY))] & NODE_PATH_E)
	{
		map[ROOM_HEIGHT / 2][ROOM_WIDTH - 1] = '.';
		map[(ROOM_HEIGHT / 2) + 1][ROOM_WIDTH - 1] = '.';
		map[(ROOM_HEIGHT / 2) - 1][ROOM_WIDTH - 1] = '.';
	}

	if (mapGen->getMapInfo()[mapGen->GetIndex(MapPosition(currRoomX, currRoomY))] & NODE_PATH_W)
	{

		map[ROOM_HEIGHT / 2][0] = '.';
		map[(ROOM_HEIGHT / 2) + 1][0] = '.';
		map[(ROOM_HEIGHT / 2) - 1][0] = '.';
	}

	ClearDetectRange();

	if (m_Rooms[currRoomY][currRoomX]->haveMon())
	{
		SpawnMon();
	}

	for (int i = 0; i < m_Rooms[currRoomY][currRoomX]->getMon().size(); i++)
	{
		GameObject* tmp;
		tmp = m_Rooms[currRoomY][currRoomX]->getMon().at(i);

		map[tmp->GetPosition().second][tmp->GetPosition().first] = 'M';

	}

	switch (m_Rooms[currRoomY][currRoomX]->getRoomType())
	{
	case 0:
		map[ROOM_HEIGHT / 2][ROOM_WIDTH / 2] = 'T';
		break;
	case 1:
		map[ROOM_HEIGHT / 2][ROOM_WIDTH / 2] = 'C';
		break;
	case 2:
		break;
	default:
		break;
	}
}

void PhaseMaze::SpawnMon()
{
	for (int i = 0; i < m_Rooms[currRoomY][currRoomX]->getMon().size(); i++)
	{
		bool randCheck = false;
		int randposX, randposY;

		while (!randCheck)
		{
			randposX = rand() % ROOM_WIDTH;
			randposY = rand() % ROOM_HEIGHT;

			if (map[randposY][randposX] != '.') {
				randCheck = false;
			}
			else
			{
				randCheck = true;
				break;
			}
		}

		m_Rooms[currRoomY][currRoomX]->getMon().at(i)->SetPosition(randposX, randposY);
	}
}

void PhaseMaze::MoveMon()
{
	if (m_Rooms[currRoomY][currRoomX]->haveMon()) {
		for (int i = 0; i < m_Rooms[currRoomY][currRoomX]->getMon().size(); i++)
		{
			GameObject* tmp = m_Rooms[currRoomY][currRoomX]->getMon().at(i);
			int randMove = rand() % 4;

			switch (randMove)
			{
			case 0:
				if ((tmp->GetPosition().first > 1) && (map[tmp->GetPosition().second][tmp->GetPosition().first - 1] == '.'))
				{
					map[tmp->GetPosition().second][tmp->GetPosition().first] = '.';

					tmp->Translate(-1, 0);
					map[tmp->GetPosition().second][tmp->GetPosition().first] = 'M';
				}
				break;
			case 1:
				if ((tmp->GetPosition().first < ROOM_HEIGHT - 2) && (map[tmp->GetPosition().second][tmp->GetPosition().first + 1] == '.'))
				{
					map[tmp->GetPosition().second][tmp->GetPosition().first] = '.';

					tmp->Translate(1, 0);
					map[tmp->GetPosition().second][tmp->GetPosition().first] = 'M';
				}
				break;
			case 2:
				if ((tmp->GetPosition().second > 1) && (map[tmp->GetPosition().second - 1][tmp->GetPosition().first] == '.'))
				{
					map[tmp->GetPosition().second][tmp->GetPosition().first] = '.';

					tmp->Translate(0, -1);
					map[tmp->GetPosition().second][tmp->GetPosition().first] = 'M';
				}
				break;
			case 3:
				if ((tmp->GetPosition().second < ROOM_HEIGHT - 2) && (map[tmp->GetPosition().second + 1][tmp->GetPosition().first] == '.'))
				{
					map[tmp->GetPosition().second][tmp->GetPosition().first] = '.';

					tmp->Translate(0, 1);
					map[tmp->GetPosition().second][tmp->GetPosition().first] = 'M';
				}
				break;
			default:
				break;
			}
		}
	}
}
