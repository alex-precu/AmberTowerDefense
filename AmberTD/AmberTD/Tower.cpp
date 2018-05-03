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

void Tower::SetFireRate(float rate)
{
	fireRate = rate;
}
float Tower::GetFireRate()
{
	return fireRate;
}
void Tower::Update(sf::RenderWindow &window)
{
	if (isBuilt)
	{
		
	}
	else
	{
		this->setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	}

}

bool Tower::GetIsReadyToFire()
{
	return isReadyToFire;
}

void Tower::SetIsReadyToFire(bool ready)
{
	isReadyToFire = ready;
}

sf::CircleShape Tower::DrawPlacementAssist(sf::RenderWindow &window)
{ 
	rangeHelper.setRadius(range);
	rangeHelper.setFillColor(sf::Color::Transparent);
	rangeHelper.setOutlineColor(this->getFillColor());
	rangeHelper.setOutlineThickness(3);
	rangeHelper.setOrigin(sf::Vector2f(this->GetRange(), this->GetRange()) );
	rangeHelper.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	return rangeHelper;
}

std::string Tower::GetName()
{
	return name;
}

Tower::Tower(int xPos, int yPos, TowerType type) : damage{ 10 }, range{ 120 }, price{ 100 }, fireRate{ 2 }, level{1}
{
	this->setPointCount(3);
	this->setPoint(0, sf::Vector2f(TILE_SIZE/2, TILE_SIZE/4));
	this->setPoint(1, sf::Vector2f(TILE_SIZE*0.75 , TILE_SIZE*0.75));
	this->setPoint(2, sf::Vector2f(TILE_SIZE*0.25, TILE_SIZE*0.75));
	this->setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
	this->setPosition(sf::Vector2f(xPos, yPos));
	this->type = type;
	if (type == TowerType::basic)
	{
		this->setFillColor(sf::Color(128, 128, 128));
	}
	else
	{
		this->setFillColor(type == TowerType::fire ? sf::Color(255, 0, 0) : sf::Color(0, 0, 255));
	}
}
TowerType Tower::GetType()
{
	return type;
}

int Tower::GetPrice()
{
	return price;
}

void Tower::SetState()
{
	isBuilt = true;
}

bool Tower::GetIsBuilt()
{
	return isBuilt;
}
Tower::Tower()
{

}

Tower::~Tower()
{
}
