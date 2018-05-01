#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "enums.h"

class Tower : public sf::CircleShape
{
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
	Tower(int xPos, int yPos);
	~Tower();
	void UpgradeLevel();
	int GetLevel();
	float GetDamage(); 
	float GetRange();
	float GetFireRate();
	void Update();
	sf::Vector2f GetPosition();
	

};

