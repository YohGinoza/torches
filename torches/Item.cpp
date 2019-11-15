#include "Item.h"
#include "Player.h"

#define HEAL_AMOUNT 10

Item::Item()
{
}


Item::~Item()
{
}

Healer::Healer()
{
}


Healer::~Healer()
{
}

void Healer::OnRead() {
	Player::GetInstance()->Heal(HEAL_AMOUNT);
}

Lighter::Lighter()
{
}


Lighter::~Lighter()
{
}

void Lighter::OnRead() {

}