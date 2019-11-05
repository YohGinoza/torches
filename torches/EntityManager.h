#pragma once
class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	static EntityManager* GetInstance();
private:
	static EntityManager* s_Instance();
};

