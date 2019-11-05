#include "Renderer.h"
#include <iostream>

Renderer* Renderer::s_Instance;

Renderer::Renderer()
{
	if (s_Instance == nullptr) {
		s_Instance = new Renderer();
	}
	else {
		delete this;
		return;
	}
}

Renderer::~Renderer()
{
}

Renderer* Renderer::GetInstance() {
	return s_Instance;
}
void Renderer::Draw(Screen& screen, Entity* entity) {
	if (entity->GetPosition().first + entity->m_Sprite->m_Dimension.first > screen.GetScreenWidth() ||
		entity->GetPosition().second + entity->m_Sprite->m_Dimension.second > screen.GetScreenHeight() ||
		entity->GetPosition().first < 0 ||
		entity->GetPosition().second < 0) {
		std::cout << "Entity out of bound";
		return;
	}
	int row = 0;
	int column = 0;
	for (int i = entity->GetPosition().second; i < entity->GetPosition().second + entity->m_Sprite->m_Dimension.second; i++, row++) {
		for (int j = entity->GetPosition().first; j < entity->GetPosition().first + entity->m_Sprite->m_Dimension.first; j++, column++) {		
			if (entity->m_Sprite->m_Image[row][column] == '1') {
				screen.SetData(i, j, '#');
			}
			else {
				screen.SetData(i, j, ' ');
			}
		}
		column = 0;
	}
	ShowOutput(screen);
}

void Renderer::Draw(Screen& screen, std::pair<int, int> position, Sprite* sprite) {
	if (position.first + sprite->m_Dimension.first > screen.GetScreenWidth() ||
		position.second + sprite->m_Dimension.second > screen.GetScreenHeight() ||
		position.first < 0 ||
		position.second < 0) {
		std::cout << "Entity out of bound";
		return;
	}

	int row = 0;
	int column = 0;
	for (int i = position.second; i < position.second + sprite->m_Dimension.second; i++, row++) {
		for (int j = position.first; j < position.first + sprite->m_Dimension.first; j++, column++) {
			if (sprite->m_Image[row][column] == '0') {
				screen.SetData(i, j, ' ');				
			}
			else {
				screen.SetData(i, j, 'o');
			}
		}
		column = 0;
	}
	ShowOutput(screen);
}

void Renderer::ShowOutput(Screen& screen) {
	std::string buffer;
	for (int i = 0; i < screen.GetScreenHeight(); i++) {
		buffer += screen.GetScanline(i);
		buffer += '\n';
	}
	std::cout << buffer;
}