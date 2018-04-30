#include "GroundTile.h"



GroundTile::GroundTile(int xPos, int yPos, int type)
{
	this->setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	this->setPosition(sf::Vector2f(xPos, yPos));
	this->setFillColor(type == GroundType::hill ? sf::Color(100, 255, 100) : sf::Color(0, 0, 0));
}
GroundTile::~GroundTile()
{
}

void GroundTile::SetOcupy(bool state)
{
	isOccupied = state;
}

void GroundTile::SetType(GroundType type)
{
	tileType = type;
}

char GroundTile::GetTiletype()
{
	return tileType;
}