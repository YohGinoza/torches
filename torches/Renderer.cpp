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
	if (entity->GetPosition().first + entity->m_Sprite->m_Dimension.first < 0 ||
		entity->GetPosition().second + entity->m_Sprite->m_Dimension.second < 0 ||
		entity->GetPosition().first > screen.GetScreenWidth() ||
		entity->GetPosition().second > screen.GetScreenHeight()) {
		return;
	}
	int spriteRow = 0;
	unsigned long long onBit = 1;
	for (int i = entity->GetPosition().second; i < entity->GetPosition().second + entity->m_Sprite->m_Dimension.second; i++, spriteRow++) {
		onBit <<= (entity->m_Sprite->m_Dimension.first - 1);
		for (int j = entity->GetPosition().first; j < entity->GetPosition().first + entity->m_Sprite->m_Dimension.first; j++) {				
			if (i < 0 || j < 0 || i > screen.GetScreenHeight() - 1 || j > screen.GetScreenWidth() - 1) {				
				onBit >>= 1;
				continue;
			}
			
			if (entity->m_Sprite->m_ImageData[spriteRow] & onBit) {
				screen.SetData(i, j, entity->m_Sprite->GetBitOnChar());
			}			
			onBit >>= 1;
		}
		onBit = 1;
	}
}

void Renderer::Draw(Screen& screen, std::pair<int, int> position, Sprite* sprite) {
	if (position.first > screen.GetScreenWidth() ||
		position.second > screen.GetScreenHeight() ||
		position.first + sprite->m_Dimension.first < 0 ||
		position.second + sprite->m_Dimension.second < 0) {
		return;
	}	
	int spriteRow = 0;
	unsigned long long onBit = 1;
	for (int i = position.second; i < position.second + sprite->m_Dimension.second; i++, spriteRow++) {
		onBit <<= (sprite->m_Dimension.first - 1);
		for (int j = position.first; j < position.first + sprite->m_Dimension.first; j++) {
			if (i < 0 || j < 0 || i > screen.GetScreenHeight() - 1 || j > screen.GetScreenWidth() - 1) {
				onBit >>= 1;
				continue;
			}
			if (sprite->m_ImageData[spriteRow] & onBit) {
				screen.SetData(i, j, sprite->GetBitOnChar());
			}			
			onBit >>= 1;
		}
		onBit = 1;
	}
}

void Renderer::ShowOutput(Screen& screen) {
	std::string buffer;	
	for (int i = 0; i < screen.GetScreenHeight(); i++) {
		buffer += screen.GetScanline(i);
		buffer += '|';
		buffer += '\n';
	}
	std::cout << buffer;
}