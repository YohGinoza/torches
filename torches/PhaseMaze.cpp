#include "PhaseMaze.h"
#include "Game.h"

PhaseMaze* PhaseMaze::s_Instance = nullptr;

PhaseMaze* PhaseMaze::GetInstance() {
	if (s_Instance == nullptr) {
		s_Instance = new PhaseMaze();
	}

	return s_Instance;
}

PhaseMaze::PhaseMaze()
{
	map = new char*[room_height];
	map_detect = new bool*[room_height];

	for (int i = 0; i < room_height; i++)
	{
		map[i] = new char[room_width];
		map_detect[i] = new bool[room_width];
	}

	for (int i = 0; i < room_height; i++)
	{
		for (int j = 0; j < room_width; j++)
		{
			map[i][j] = '.';
			map_detect[i][j] = false;
		}
	}

	for (int i = 0; i < room_width; i++)
	{
		map[0][i] = '#';
		map[room_height - 1][i] = '#';

		map_detect[0][i] = true;
		map_detect[room_height - 1][i] = true;
	}

	for (int i = 0; i < room_height; i++)
	{
		map[i][0] = '#';
		map[i][room_width - 1] = '#';

		map_detect[i][0] = true;
		map_detect[i][room_width - 1] = true;
	}

	map[room_height / 2][room_width / 2] = 'T';

	debug_draw = false;

	player = Player::GetInstance();

	player->SetPosition(2, room_height / 2);

	std::cout << player->GetPosition().first << " " << player->GetPosition().second << std::endl;
	
	map[player->GetPosition().second][player->GetPosition().first] = '@';
}

void PhaseMaze::Draw_Debug() 
{
	for (int i = 0; i < room_height; i++)
	{
		for (int j = 0; j < room_width; j++) 
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


PhaseMaze::~PhaseMaze()
{
}

void PhaseMaze::OnUpdate(float dt) 
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
			if ((player_posX < room_width - 2) && (map[player_posY][player_posX + 1] == '.'))
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
			if ((player_posY < room_height - 2) && (map[player_posY + 1][player_posX] == '.'))
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
			if ((i > 0) && (i < room_height - 1) && (j > 0) && (j < room_width -1)) {

				map_detect[i][j] = true;
			}
		}
	}

	for (int i = player_posX - 1; i < player_posX + 2; i++)
	{
		if ((player_posY - 2 > 0) && (player_posY - 2 < room_height - 1) && (i > 0) && (i < room_width - 1))
		{
			map_detect[player_posY - 2][i] = true;
		}

		if ((player_posY + 2 > 0) && (player_posY + 2 < room_height - 1) && (i > 0) && (i < room_width - 1))
		{
			map_detect[player_posY + 2][i] = true;
		}
	}
}

void PhaseMaze::ClearDetectRange() 
{
	for (int i = 0; i < room_height; i++)
	{
		for (int j = 0; j < room_width; j++)
		{
			map_detect[i][j] = false;
		}
	}

	map_detect[player->GetPosition().second][player->GetPosition().first] = true;

	for (int i = 0; i < room_width; i++)
	{
		map_detect[0][i] = true;
		map_detect[room_height - 1][i] = true;
	}

	for (int i = 0; i < room_height; i++)
	{
		map_detect[i][0] = true;
		map_detect[i][room_width - 1] = true;
	}
}
