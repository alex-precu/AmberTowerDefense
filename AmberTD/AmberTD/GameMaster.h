#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class GameMaster
	
{
	std::vector<sf::CircleShape> activeActors;
	int money;
	
public:
	
	GameMaster();
	~GameMaster();
};

