#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"

class GroundTile : public sf::RectangleShape
{
	bool isOccupied = false;
	char tileType = GroundType::hill;

public:
	void SetOcupy(bool state);
	void SetType(GroundType type);
	char GetTiletype();
	GroundTile(int xPos,int yPos, int type);
	~GroundTile();
};

