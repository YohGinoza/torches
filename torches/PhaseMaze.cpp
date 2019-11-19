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

	for (int i = 0; i < ROOM_WIDTH; i++)
	{
		map[0][i] = '#';
		map[ROOM_HEIGHT - 1][i] = '#';

		map_detect[0][i] = true;
		map_detect[ROOM_HEIGHT - 1][i] = true;
	}

	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		map[i][0] = '#';
		map[i][ROOM_WIDTH - 1] = '#';

		map_detect[i][0] = true;
		map_detect[i][ROOM_WIDTH - 1] = true;
	}

	map[ROOM_HEIGHT / 2][ROOM_WIDTH / 2] = 'T';

	debug_draw = false;

	player = Player::GetInstance();

	player->SetPosition(2, ROOM_HEIGHT / 2);

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

	if (Game::getInput()->KeyPress())
	{
		system("cls");

		if (Game::getInput()->getKey(KeyCode::KEY_A)) 
		{
			if ((player_posX > 1) && (map[player_posY][player_posX - 1] == '.'))
			{
				map[player_posY][player_posX] = '.';

				player->Translate(-1, 0);
				player_posX -= 1;
				map[player_posY][player_posX] = '@';
			}
		}
		else if (Game::getInput()->getKey(KeyCode::KEY_D))
		{
			if ((player_posX < ROOM_WIDTH - 2) && (map[player_posY][player_posX + 1] == '.'))
			{
				map[player_posY][player_posX] = '.';
				
				player->Translate(1, 0);
				player_posX += 1;
				map[player_posY][player_posX] = '@';
			}
		}
		else if (Game::getInput()->getKey(KeyCode::KEY_W))
		{
			if ((player_posY > 1) && (map[player_posY - 1][player_posX] == '.'))
			{
				map[player_posY][player_posX] = '.';

				player->Translate(0, -1);
				player_posY -= 1;
				map[player_posY][player_posX] = '@';
			}
		}
		else if (Game::getInput()->getKey(KeyCode::KEY_S))
		{
			if ((player_posY < ROOM_HEIGHT - 2) && (map[player_posY + 1][player_posX] == '.'))
			{
				map[player_posY][player_posX] = '.';

				player->Translate(0, 1);
				player_posY += 1;
				map[player_posY][player_posX] = '@';
			}
		}

		std::cout << player_posX << " " << player_posY << std::endl;

		UpdateDetectRange();
		Draw_Debug();
	}
}

void PhaseMaze::UpdateDetectRange() 
{
	ClearDetectRange();

	for (int i = player_posY - 1; i < player_posY + 2; i++)
	{
		for (int j = player_posX - 2; j < player_posX + 3; j++)
		{
			if ((i > 0) && (i < ROOM_HEIGHT - 1) && (j > 0) && (j < ROOM_WIDTH -1)) {

				map_detect[i][j] = true;
			}
		}
	}

	for (int i = player_posX - 1; i < player_posX + 2; i++)
	{
		if ((player_posY - 2 > 0) && (player_posY - 2 < ROOM_HEIGHT - 1) && (i > 0) && (i < ROOM_WIDTH - 1))
		{
			map_detect[player_posY - 2][i] = true;
		}

		if ((player_posY + 2 > 0) && (player_posY + 2 < ROOM_HEIGHT - 1) && (i > 0) && (i < ROOM_WIDTH - 1))
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
}
