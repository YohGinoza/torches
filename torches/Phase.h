#pragma once
class Phase
{
public:
	Phase();
	~Phase();
	virtual void OnUpdate(float dt) = 0;
};

