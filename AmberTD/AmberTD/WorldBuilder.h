#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameMaster.h"
#include <string>
#include <vector>
#include "enums.h"
#include "GroundTile.h"
#include <math.h>

class WorldBuilder
{
	std::vector<sf::ConvexShape> map;

public:
	WorldBuilder();
	~WorldBuilder();
	void CreateWorld();
	void LoadLevel();
	std::vector<sf::ConvexShape> &GetMap();
};

