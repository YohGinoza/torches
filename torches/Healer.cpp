#include "Healer.h"
#include "Player.h"

#define HEAL_AMOUNT 10

Healer::Healer()
{
}


Healer::~Healer()
{
}

void Healer::OnRead() {
	Player::GetInstance()->Heal(HEAL_AMOUNT);
}