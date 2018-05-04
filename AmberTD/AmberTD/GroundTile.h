#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"

class GroundTile : public sf::ConvexShape
{
	bool isEmpty = true;
	char tileType = GroundType::hill;
	sf::Texture tileset;

public:
	void SetIsEmpty(bool state);
	bool GetIsEmpty();
	void SetType(GroundType type);
	char GetTiletype();
	GroundTile(int xPos,int yPos, int type);
	~GroundTile();
};

