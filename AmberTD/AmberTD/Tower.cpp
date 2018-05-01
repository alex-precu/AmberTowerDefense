#include "Tower.h"
#include "Bullet.h"

void Tower::UpgradeLevel()
{
	level++;
}

int Tower::GetLevel()
{
	return level;
}

void Tower::SetDamage()
{
	damage += GetDamage() / level;
}

float Tower::GetDamage()
{
	return damage;
}

void Tower::SetRange()
{
	range += range/5;
}

float Tower::GetRange()
{
	return range;
}
	
void Tower::SetPosition(float dx, float dy)
{
	position.x = dx;
	position.y = dy;
}

sf::Vector2f Tower::GetPosition()
{
	return position;
}

void Tower::SetFireRate(float rate)
{
	fireRate = rate;
}
float Tower::GetFireRate()
{
	return fireRate;
}
void Update()
{
	// implement Update / fire rate
}

std::string Tower::GetName()
{
	return name;
}

Tower::Tower(int xPos,int yPos,TowerType type )
{
	this->setPointCount(3);
	this->setPoint(0, sf::Vector2f(TILE_SIZE/2, 0));
	this->setPoint(1, sf::Vector2f(TILE_SIZE/2-20 , TILE_SIZE));
	this->setPoint(2, sf::Vector2f(TILE_SIZE/2+20, TILE_SIZE));

	this->setOutlineThickness(2);
	this->setPosition(sf::Vector2f(xPos, yPos));
	
	if (type == TowerType::basic)
	{
		this->setFillColor(sf::Color(128, 128, 128));
	}
	else
	{
		this->setFillColor(type == TowerType::fire ? sf::Color(255, 0, 0) : sf::Color(0, 0, 255));
	}
}

Tower::Tower()
{

}

Tower::~Tower()
{
}
