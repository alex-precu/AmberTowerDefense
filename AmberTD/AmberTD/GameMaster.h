#pragma once
#include <vector>
class GameMaster
	
{
	std::vector<Actor*> activeActors;
	int money;
	
public:
	GameMaster();
	~GameMaster();
};

