#pragma once
#include "Item.h"
class Healer :
	public Item
{
public:
	Healer();
	~Healer();
	virtual void OnRead() override;
};

