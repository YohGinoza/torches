#include "Player.h"

Player* Player::s_Instance;

Player::Player()
{
	if (s_Instance == nullptr) {
		s_Instance = new Player();
	}
	else {
		delete this;
		return;
	}
}


Player::~Player()
{
}

Player* Player::GetInstance() {
	return s_Instance;
}

void Player::Heal(int value) {
	this->Hp += value;
}
