#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "enums.h"
#include <string>


class Tower : public sf::ConvexShape
{
	std::string name = "Basic Tower";
	int level;
	float damage;
	float range;
	float fireRate;
	int price;
	sf::Vector2f position;
	void SetDamage();
	void SetRange();
	void SetPosition(float dx, float dy);
	void SetFireRate(float rate);

public:
	Tower();
	Tower(int xPos, int yPos, TowerType type);
	~Tower();
	std::string GetName();
	void UpgradeLevel();
	int GetLevel();
	float GetDamage(); 
	float GetRange();
	float GetFireRate();
	void Update();
	sf::Vector2f GetPosition();
	

};

