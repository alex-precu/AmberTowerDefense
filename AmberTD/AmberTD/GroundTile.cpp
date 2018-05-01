#include "GroundTile.h"



GroundTile::GroundTile(int xPos, int yPos, int type)
{
	this->setPointCount(4);
	this->setPoint(0, sf::Vector2f(0,0));
	this->setPoint(1, sf::Vector2f(0 + TILE_SIZE, 0));
	this->setPoint(2, sf::Vector2f(0 + TILE_SIZE, 0 +TILE_SIZE));
	this->setPoint(3, sf::Vector2f(0, 0+  TILE_SIZE));

	//this->setOutlineThickness(3);
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