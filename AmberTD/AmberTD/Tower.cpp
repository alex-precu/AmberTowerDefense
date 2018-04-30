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

Tower::Tower(int xPos,int yPos)
{
	this->setRadius(TILE_SIZE/2);
	this->setPosition(xPos, yPos);
	this->setFillColor(sf::Color(255, 0, 127));
}
Tower::Tower()
{

}

Tower::~Tower()
{
}
