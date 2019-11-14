#pragma once
#include "Item.h"
class Lighter :
	public Item
{
public:
	Lighter();
	~Lighter();
	virtual void OnRead() override;
};

