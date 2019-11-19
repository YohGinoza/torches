#include "Player.h"

Player* Player::s_Instance;

Player::Player()
{
	Hp = 100;
}


Player::~Player()
{

}

Player* Player::GetInstance() {
	if (s_Instance == nullptr) {
		s_Instance = new Player();
	}
	
	return s_Instance;
}

void Player::Heal(int value) {
	this->Hp += value;
}
